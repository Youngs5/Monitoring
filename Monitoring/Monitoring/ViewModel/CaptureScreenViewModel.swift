//
//  CaptureScreenViewModel.swift
//  Monitoring
//
//  Created by 오영석 on 11/1/23.
//

import Foundation
import AppKit

class CaptureScreenViewModel {
    var timer: Timer?
    var isCapturing: Bool = false
    var yoloService: YoloService
    
    var onScreenCaptured: ((NSImage?) -> Void)?
    var onPersonDetected: ((Bool) -> Void)?
    var analyzeScreenViewModel: AnalyzeScreenViewModel?
    
    init(yoloService: YoloService, analyzeScreenViewModel: AnalyzeScreenViewModel) {
        self.yoloService = yoloService
        self.analyzeScreenViewModel = analyzeScreenViewModel
    }
    
    func startCapture() {
         guard !isCapturing else { return }

         timer = Timer.scheduledTimer(withTimeInterval: 5.0, repeats: true) { [weak self] _ in
             guard let self = self else { return }

             guard let capturedImage = self.captureScreen() else {
                 print("Failed to capture screen")
                 return
             }
             self.onScreenCaptured?(NSImage(cgImage: capturedImage, size: NSSize(width: capturedImage.width, height: capturedImage.height)))

             self.yoloService.detectPeople(image: capturedImage) { [weak self] isPersonDetected in
                 self?.onPersonDetected?(isPersonDetected)

                 if isPersonDetected {
                     self?.analyzeScreenViewModel?.analyzeScreen(image: NSImage(cgImage: capturedImage, size: NSSize(width: capturedImage.width, height: capturedImage.height)))
                 }
             }
         }
         isCapturing = true
     }
    
    func stopCapture() {
        timer?.invalidate()
        isCapturing = false
    }
    
    private func captureScreen() -> CGImage? {
        guard let screen = NSScreen.main else {
            return nil
        }
        
        let screenFrame = screen.frame
        let screenRect = CGRect(x: 0, y: 0, width: screenFrame.width, height: screenFrame.height)
        
        if let screenShot = CGDisplayCreateImage(CGMainDisplayID(), rect: screenRect) {
            print("Screen captured successfully")
            return screenShot
        }
        
        print("Failed to capture screen")
        return nil
    }
}
