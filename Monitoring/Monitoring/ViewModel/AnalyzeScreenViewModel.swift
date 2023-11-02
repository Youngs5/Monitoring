//
//  AnalyzeScreenViewModel.swift
//  Monitoring
//
//  Created by 오영석 on 11/1/23.
//

import Foundation
import AppKit

class AnalyzeScreenViewModel {
    let yoloService: YoloService
    
    init(yoloService: YoloService) {
        self.yoloService = yoloService
    }
    
    func analyzeScreen(image: NSImage) {
        guard let cgImage = image.cgImage(forProposedRect: nil, context: nil, hints: nil) else { return }
        yoloService.detectObjects(image: cgImage) { detectedLabels in
            self.executeActionsBasedOnDetectedLabels(detectedLabels)
        }
    }
    
    private func executeActionsBasedOnDetectedLabels(_ detectedLabels: [String]) {
        for label in detectedLabels {
            switch label {
            case "person": break
            case "object2": break
                default:
                    break
            }
        }
    }
}


