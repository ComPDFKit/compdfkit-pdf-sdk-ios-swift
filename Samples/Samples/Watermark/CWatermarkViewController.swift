//
//  CWatermarkViewController.swift
//  Samples
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

import UIKit
import ComPDFKit

//-----------------------------------------------------------------------------------------
// The sample code illustrates how to add and remove watermarks, including text
// and image watermarks. date using API.
//-----------------------------------------------------------------------------------------

class CWatermarkViewController: CSamplesBaseViewController {
    var isRun = false
    var commandLineStr = ""
    var addTextWatermarkURL:URL?
    var addTilesWatermarkURL:URL?
    var addImageWatermarkURL:URL?
    var deleteWatermarkURL:URL?
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to add watermarks, including text, image and tile watermarks, and delete watermarks.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }

    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        // Determine whether to export the document
            if self.isRun {
                let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
                
                if UIDevice.current.userInterfaceIdiom == .pad {
                    alertController.popoverPresentationController?.sourceView = self.openfileButton
                    alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
                }
                
                let textWatermarkAction = UIAlertAction(title: NSLocalizedString("   AddTextWatermarkTest.pdf   ", comment: ""), style: .default) { [weak self] action in
                    // Open AddTextWatermarkTest.pdf
                    if let url = self?.addTextWatermarkURL {
                        self?.openFile(with: url)
                    }
                }
                
                let imageWatermarkAction = UIAlertAction(title: NSLocalizedString("   AddImageWatermarkTest.pdf   ", comment: ""), style: .default) { [weak self] action in
                    // Open AddImageWatermarkTest.pdf
                    if let url = self?.addImageWatermarkURL {
                        self?.openFile(with: url)
                    }
                }
                
                let tilesWatermarkAction = UIAlertAction(title: NSLocalizedString("   AddTilesWatermarkTest.pdf   ", comment: ""), style: .default) { [weak self] action in
                    // Open AddTilesWatermarkTest.pdf
                    if let url = self?.addTilesWatermarkURL {
                        self?.openFile(with: url)
                    }
                }
                
                let deleteWatermarkAction = UIAlertAction(title: NSLocalizedString("   DeleteWatermarkTest.pdf   ", comment: ""), style: .default) { [weak self] action in
                    // Open DeleteWatermarkTest.pdf
                    if let url = self?.deleteWatermarkURL {
                        self?.openFile(with: url)
                    }
                }
                
                let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
                
                alertController.addAction(textWatermarkAction)
                alertController.addAction(imageWatermarkAction)
                alertController.addAction(tilesWatermarkAction)
                alertController.addAction(deleteWatermarkAction)
                alertController.addAction(cancelAction)
                
                present(alertController, animated: false, completion: nil)
            } else {
                let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
                
                if UIDevice.current.userInterfaceIdiom == .pad {
                    alertController.popoverPresentationController?.sourceView = self.openfileButton
                    alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
                }
                
                let noAction = UIAlertAction(title: NSLocalizedString("No files for this sample.", comment: ""), style: .default, handler: nil)
                let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
                
                alertController.addAction(noAction)
                alertController.addAction(cancelAction)
                
                present(alertController, animated: false, completion: nil)
            }
    }
    
    override func buttonItemClick_run(_ sender: Any) {
        if document != nil {
                self.isRun = true
                
                self.commandLineStr = self.commandLineStr + "Running Watermark sample...\n\n"
                self.addTextWatermark(document)
                self.addImageWatermark(document)
                self.addTilesWatermark(document)
                self.deleteWatermark()
                self.commandLineStr = self.commandLineStr + "\nDone!\n"
                self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
                
                // Refresh commandline message
                self.commandLineTextView.text = self.commandLineStr
            } else {
                self.isRun = false
                self.commandLineStr = self.commandLineStr + "The document is null, can't open..\n\n"
                self.commandLineTextView.text = self.commandLineStr
            }
    }
    
    // MARK: -  Samples Methods
    func addTextWatermark(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 1: Insert text watermark\n"

        // Get Sandbox path for saving the PDF file
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
        let writeDirectoryPath = path.appendingPathComponent("Watermark")

        if !FileManager.default.fileExists(atPath: writeDirectoryPath.path) {
            try? FileManager.default.createDirectory(at: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath.appendingPathComponent("AddTextWatermarkTest.pdf")
        
        // Save the document in the test PDF file
        addTextWatermarkURL = writeFilePath
        oldDocument?.write(to: addTextWatermarkURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: addTextWatermarkURL)
        
        // Create text watermark
        let watermark = CPDFWatermark(document: document, type: .text)
        
        watermark?.text = "ComPDFKit"
        watermark?.textFont = UIFont(name: "Helvetica", size: 30) ?? UIFont.systemFont(ofSize: 30)
        watermark?.textColor = UIColor.red
        watermark?.scale = 2.0
        watermark?.rotation = 45
        watermark?.opacity = 0.5
        watermark?.verticalPosition = .center
        watermark?.horizontalPosition = .center
        watermark?.tx = 0.0
        watermark?.ty = 0.0
        watermark?.isFront = true
        watermark?.isTilePage = false
        watermark?.pageString = "0-4"
        document?.addWatermark(watermark)
        document?.updateWatermark(watermark)
        
        document?.write(to: addTextWatermarkURL)
        
        // Print text watermark object message
        commandLineStr += "Text: \(watermark?.text ?? "")\n"
        var red: CGFloat = 0
        var green: CGFloat = 0
        var blue: CGFloat = 0
        var alpha: CGFloat = 0
        watermark?.textColor.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
        commandLineStr += String(format: "Color: red:%.1f, green:%.1f, blue:%.1f, alpha:%.1f\n", red, green, blue, alpha)
        commandLineStr += String(format: "FontSize: %.1f\n", watermark?.textFont.pointSize ?? 0)
        commandLineStr += String(format: "Opacity: %.1f\n", watermark?.opacity ?? 0)
        commandLineStr += "Vertalign: \(getStringFromEnumVertalign((watermark?.verticalPosition)?.rawValue ?? 0))\n"
        commandLineStr += "Horizalign: \(getStringFromEnumHorizalign((watermark?.horizontalPosition)?.rawValue ?? 0))\n"
        commandLineStr += String(format: "VertOffset: %.1f\n", watermark?.tx ?? 0)
        commandLineStr += String(format: "HorizOffset: %.1f\n", watermark?.ty ?? 0)
        commandLineStr += "Pages: \(watermark?.pageString ?? "")\n"
        commandLineStr += String(format: "VerticalSpacing: %.1f\n", watermark?.verticalSpacing ?? 0)
        commandLineStr += String(format: "HorizontalSpacing: %.1f\n", watermark?.horizontalSpacing ?? 0)
        commandLineStr += "Done. Results saved in AddTextWatermarkTest.pdf\n"
    }
    
    func addImageWatermark(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 2: Insert Image Watermark\n"
        
        // Get Sandbox path for saving the PDF file
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
        let writeDirectoryPath = path.appendingPathComponent("Watermark")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath.path) {
            try? FileManager.default.createDirectory(at: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath.appendingPathComponent("AddImageWatermarkTest.pdf")
        
        // Save the document in the test PDF file
        addImageWatermarkURL = writeFilePath
        oldDocument?.write(to: addImageWatermarkURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: addImageWatermarkURL)
        
        // Create an image watermark
        let watermark = CPDFWatermark(document: document, type: .image)
        
        if let image = UIImage(named: "Logo") {
            watermark?.image = image
        }
        
        watermark?.scale = 2.0
        watermark?.rotation = 45
        watermark?.opacity = 0.5
        watermark?.verticalPosition = .center
        watermark?.horizontalPosition = .center
        watermark?.tx = 0.0
        watermark?.ty = 0.0
        watermark?.isFront = true
        watermark?.pageString = "0-4"
        document?.addWatermark(watermark)
        
        document?.write(to: addImageWatermarkURL)
        
        // Print image watermark object message
        commandLineStr += String(format: "Opacity: %.1f\n", watermark?.opacity ?? 0)
        commandLineStr += "Vertalign: \((watermark?.verticalPosition)?.rawValue ?? 0)\n"
        commandLineStr += "Horizalign: \(getStringFromEnumHorizalign((watermark?.horizontalPosition)?.rawValue ?? 0))\n"
        commandLineStr += String(format: "VertOffset: %.1f\n", watermark?.tx ?? 0)
        commandLineStr += String(format: "HorizOffset: %.1f\n", watermark?.ty ?? 0)
        commandLineStr += "Pages: \(watermark?.pageString ?? "")\n"
        commandLineStr += String(format: "VerticalSpacing: %.1f\n", watermark?.verticalSpacing ?? 0)
        commandLineStr += String(format: "HorizontalSpacing: %.1f\n", watermark?.horizontalSpacing ?? 0)
        commandLineStr += "Done. Results saved in AddImageWatermarkTest.pdf\n"
    }
    
    func addTilesWatermark(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 3: Insert Text Tiles Watermark\n"
        
        // Get Sandbox path for saving the PDF file
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
        let writeDirectoryPath = path.appendingPathComponent("Watermark")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath.path) {
            try? FileManager.default.createDirectory(at: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath.appendingPathComponent("AddTilesWatermarkTest.pdf")
        
        // Save the document in the test PDF file
        addTilesWatermarkURL = writeFilePath
        oldDocument?.write(to: addTilesWatermarkURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: addTilesWatermarkURL)
        
        // Create text tiles watermark
        let watermark = CPDFWatermark(document: document, type: .text)
        
        watermark?.text = "ComPDFKit"
        watermark?.textFont = UIFont(name: "Helvetica", size: 30)
        watermark?.textColor = UIColor.red
        watermark?.scale = 2.0
        watermark?.rotation = 45
        watermark?.opacity = 0.5
        watermark?.verticalPosition = .center
        watermark?.horizontalPosition = .center
        watermark?.tx = 0.0
        watermark?.ty = 0.0
        watermark?.isFront = true
        watermark?.isTilePage = true
        watermark?.verticalSpacing = 10
        watermark?.horizontalSpacing = 10
        watermark?.pageString = "0-4"
        document?.addWatermark(watermark)
        
        document?.write(to: addTilesWatermarkURL)
        
        // Print text tiles watermark object message
        commandLineStr += String(format: "Text: %@\n", watermark?.text ?? "")
        var red: CGFloat = 0.0, green: CGFloat = 0.0, blue: CGFloat = 0.0, alpha: CGFloat = 0.0
        watermark?.textColor?.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
        commandLineStr += String(format: "Color: red: %.1f, green: %.1f, blue: %.1f, alpha: %.1f\n", red, green, blue, alpha)
        commandLineStr += String(format: "FontSize: %.1f\n", watermark?.textFont?.pointSize ?? 0.0)
        commandLineStr += String(format: "Opacity: %.1f\n", watermark?.opacity ?? 0)
        commandLineStr += "Vertalign: \(getStringFromEnumVertalign((watermark?.verticalPosition)?.rawValue ?? 0))\n"
        commandLineStr += "Horizalign: \(getStringFromEnumHorizalign((watermark?.horizontalPosition)?.rawValue ?? 0))\n"
        commandLineStr += String(format: "VertOffset: %.1f\n", watermark?.tx ?? 0)
        commandLineStr += String(format: "HorizOffset: %.1f\n", watermark?.ty ?? 0)
        commandLineStr += String(format: "Pages: %@\n", watermark?.pageString ?? "")
        commandLineStr += String(format: "VerticalSpacing: %.1f\n", (watermark?.verticalSpacing ?? 0))
        commandLineStr += String(format: "HorizontalSpacing: %.1f\n", (watermark?.horizontalSpacing ?? 0))
        commandLineStr += "Done. Results saved in AddTilesWatermarkTest.pdf\n"
    }
    
    func deleteWatermark() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 4: Delete Watermark\n"
        
        // Get Sandbox path for saving the PDF File
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
        let writeDirectoryPath = path.appendingPathComponent("Watermark")
        let documentFolder = path.appendingPathComponent("Documents").appendingPathComponent("Watermark").appendingPathComponent("AddTextWatermarkTest.pdf")
        
        // Copy file
        if !FileManager.default.fileExists(atPath: writeDirectoryPath.path) {
            try? FileManager.default.createDirectory(at: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath.appendingPathComponent("DeleteWatermarkTest.pdf")
        
        if FileManager.default.fileExists(atPath: documentFolder.path) {
            try? FileManager.default.copyItem(at: documentFolder, to: writeFilePath)
        }
        
        deleteWatermarkURL = writeFilePath
        let document = CPDFDocument(url: deleteWatermarkURL)
        
        if let waterArray = document?.watermarks(), !waterArray.isEmpty {
            document?.removeWatermark(waterArray[0])
        }
        
        document?.write(to: deleteWatermarkURL)
        
        commandLineStr += "Done. Results saved in DeleteWatermarkTest.pdf\n"
    }
    
    func getStringFromEnumVertalign(_ enums: Int) -> String {
        switch enums {
        case 0:
            return "CPDFWatermarkVerticalPositionTop"
        case 1:
            return "CPDFWatermarkVerticalPositionCenter"
        case 2:
            return "CPDFWatermarkVerticalPositionBottom"
        default:
            return " "
        }
    }

    func getStringFromEnumHorizalign(_ enums: Int) -> String {
        switch enums {
        case 0:
            return "CPDFWatermarkHorizontalPositionLeft"
        case 1:
            return "CPDFWatermarkHorizontalPositionCenter"
        case 2:
            return "CPDFWatermarkHorizontalPositionRight"
        default:
            return " "
        }
    }

    func openFile(with url: URL) {
        let activityVC = UIActivityViewController(activityItems: [url], applicationActivities: nil)
        activityVC.definesPresentationContext = true
        if UIDevice.current.userInterfaceIdiom == .pad {
            activityVC.popoverPresentationController?.sourceView = openfileButton
            activityVC.popoverPresentationController?.sourceRect = openfileButton.bounds
        }
        
        present(activityVC, animated: true, completion: nil)
        
        activityVC.completionWithItemsHandler = { activityType, completed, returnedItems, activityError in
            if completed {
                print("Success!")
            } else {
                print("Failed Or Canceled!")
            }
        }
    }





}
