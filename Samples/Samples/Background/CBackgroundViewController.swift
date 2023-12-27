//
//  CBackgroundViewController.swift
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
// The sample code illustrates how to add and remove background, including text
// and image background. date using API.
//-----------------------------------------------------------------------------------------

class CBackgroundViewController: CSamplesBaseViewController {
    
    var isRun: Bool = false
    var commandLineStr: String = ""
    var addColorBackgroundURL: URL?
    var addImageBackgroundURL: URL?
    var deleteBackgroundURL: URL?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to add color and picture backs and delete backgrounds.", comment: "")
        self.commandLineTextView.text = ""
        self.isRun = false
        self.commandLineStr = ""
    }
    
    // MARK: - Action
    @IBAction override func buttonItemClick_openFile(_ sender: Any)  {
        if self.isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            
            let colorBackgroundAction = UIAlertAction(title: NSLocalizedString("   AddColorBackgroundTest.pdf   ", comment: ""), style: .default) { (action) in
                // Open AddColorBackgroundTest.pdf
                if(self.addColorBackgroundURL != nil) {
                    self.openFileWithURL(self.addColorBackgroundURL!)
                }
            }
            
            let imageBackgroundAction = UIAlertAction(title: NSLocalizedString("   AddImageBackgroundTest.pdf   ", comment: ""), style: .default) { (action) in
                // Open AddImageBackgroundTest.pdf
                if(self.addImageBackgroundURL != nil) {
                    self.openFileWithURL(self.addImageBackgroundURL!)
                }
            }
            
            let deleteBackgroundAction = UIAlertAction(title: NSLocalizedString("   DeleteBackgroundTest.pdf   ", comment: ""), style: .default) { (action) in
                // Open DeleteBackgroundTest.pdf
                if(self.deleteBackgroundURL != nil) {
                    self.openFileWithURL(self.deleteBackgroundURL!)
                }
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(colorBackgroundAction)
            alertController.addAction(imageBackgroundAction)
            alertController.addAction(deleteBackgroundAction)
            alertController.addAction(cancelAction)
            
            self.present(alertController, animated: false, completion: nil)
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
            
            self.present(alertController, animated: false, completion: nil)
        }
        
    }
    
    @IBAction override func buttonItemClick_run(_ sender: Any)  {
        if self.document != nil {
            self.isRun = true
            
            self.commandLineStr += "Running Watermark sample...\n\n"
            self.addColorBackground(document)
            self.addImageBackground(document)
            self.deleteColorBackground()
            self.commandLineStr += "\nDone!\n"
            self.commandLineStr += "-------------------------------------\n"
            
            // Refresh commandline message
            self.commandLineTextView.text = self.commandLineStr
        } else {
            self.isRun = false
            self.commandLineStr += "The document is null, can't open..\n\n"
            self.commandLineTextView.text = self.commandLineStr
        }
    }
    
    // MARK: - Samples Methods
    
    func addColorBackground(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 1 : Set the document background color\n"
        
        // Get Sandbox path for saving the PDFFile
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first
        let writeDirectoryPath = path?.appendingPathComponent("Background")
        
        do {
            try FileManager.default.createDirectory(at: writeDirectoryPath!, withIntermediateDirectories: true, attributes: nil)
        } catch {
            print("Error creating directory: \(error)")
        }
        
        let writeFilePath = writeDirectoryPath?.appendingPathComponent("AddColorBackgroundTest.pdf")
        
        // Save the document in the test PDF file
        if let writeFilePath = writeFilePath {
            oldDocument?.write(to: writeFilePath)
            addColorBackgroundURL = writeFilePath
        }
        
        // Create a new document for the test PDF file
        if let document = CPDFDocument(url: addColorBackgroundURL) {
            // Create color background
            if let background = document.background() {
                background.type = .color
                background.color = .red // Background color (image background does not work).
                background.opacity = 1.0 // Background transparency, the range of 0~1, with the default of 1.
                background.scale = 1.0 // Background tiling scale.
                background.rotation = 0 // Background rotation angle, the range of 0~360, the default is 0 (rotate at the centre of the page).
                background.horizontalAlignment = 1 // Background vertical alignment. `0` for top alignment, `1` for centre alignment, `1` for bottom alignment.
                background.verticalAlignment = 1 // Horizontal alignment of the background. `0` for left alignment, `1` for centre alignment, `1` for right alignment.
                background.xOffset = 0 // The horizontal offset of the background. Positive numbers are shifted to the right, negative numbers are shifted to the left.
                background.yOffset = 0 // The vertical offset of the background. Positive numbers are shifted downwards, negative numbers are shifted upwards.
                
                background.pageString = "0,1,2,3,4" // Background page range, such as "0,3,5-7".
                
                background.update()
                
                // Print color background object message
                commandLineStr += "Type : Color"
                var red: CGFloat = 0, green: CGFloat = 0, blue: CGFloat = 0, alpha: CGFloat = 0
                background.color.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
                commandLineStr += String(format: "Color : red:%.1f, green:%.1f, blue:%.1f, alpha:%.1f\n", red, green, blue, alpha)
                commandLineStr += String(format: "Opacity :%.1f\n", background.opacity)
                commandLineStr += String(format: "Rotation :%.1f\n", background.rotation)
                commandLineStr += String(format: "Vertalign :%@\n", getStringFromEnumVertalign(Int(background.verticalAlignment)))
                commandLineStr += String(format: "Horizalign :%@\n", getStringFromEnumHorizalign(Int(background.horizontalAlignment)))
                commandLineStr += String(format: "VertOffset :%.1f\n", background.xOffset)
                commandLineStr += String(format: "HorizOffset :%.1f\n", background.yOffset)
                commandLineStr += String(format: "Pages :%@\n", background.pageString)
                commandLineStr += "Done. Results saved in AddColorBackgroundTest.pdf\n"
            }
        }
    }
    
    func addImageBackground(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 2 : Set the document background image\n"
        
        // Get Sandbox path for saving the PDFFile
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first
        let writeDirectoryPath = path?.appendingPathComponent("Background")
        
        do {
            try FileManager.default.createDirectory(at: writeDirectoryPath!, withIntermediateDirectories: true, attributes: nil)
        } catch {
            print("Error creating directory: \(error)")
        }
        
        let writeFilePath = writeDirectoryPath?.appendingPathComponent("AddImageBackgroundTest.pdf")
        
        // Save the document in the test PDF file
        if let writeFilePath = writeFilePath {
            oldDocument?.write(to: writeFilePath)
            addImageBackgroundURL = writeFilePath
        }
        
        // Create a new document for the test PDF file
        if let document = CPDFDocument(url: addImageBackgroundURL) {
            // Create image background
            if let background = document.background() {
                background.type = .image
                background.setImage(UIImage(named: "Logo"))
                background.opacity = 1.0 // Background transparency, the range of 0~1, with the default of 1.
                background.scale = 1.0 // Background tiling scale.
                background.rotation = 0 // Background rotation angle, the range of 0~360, the default is 0 (rotate at the centre of the page).
                background.horizontalAlignment = 1 // Background vertical alignment. `0` for top alignment, `1` for centre alignment, `1` for bottom alignment.
                background.verticalAlignment = 1 // Horizontal alignment of the background. `0` for left alignment, `1` for centre alignment, `1` for right alignment.
                background.xOffset = 0 // The horizontal offset of the background. Positive numbers are shifted to the right, negative numbers are shifted to the left.
                background.yOffset = 0 // The vertical offset of the background. Positive numbers are shifted downwards, negative numbers are shifted upwards.
                
                background.pageString = "0,1,2,3,4" // Background page range, such as "0,3,5-7".
                
                background.update()
                
                // Print image background object message
                commandLineStr += "Type : Image\n"
                commandLineStr += String(format: "Opacity :%.1f\n", background.opacity)
                commandLineStr += String(format: "Rotation :%.1f\n", background.rotation)
                commandLineStr += String(format: "Vertalign :%@\n", getStringFromEnumVertalign(Int(background.verticalAlignment)))
                commandLineStr += String(format: "Horizalign :%@\n", getStringFromEnumHorizalign(Int(background.horizontalAlignment)))
                commandLineStr += String(format: "VertOffset :%.1f\n", background.xOffset)
                commandLineStr += String(format: "HorizOffset :%.1f\n", background.yOffset)
                commandLineStr += String(format: "Pages :%@\n", background.pageString)
                commandLineStr += "Done. Results saved in AddImageBackgroundTest.pdf\n"
            }
        }
    }
    
    func deleteColorBackground() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 3 :  Delete document background\n"
        
        // Get Sandbox path for saving the PDFFile
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first
        let writeDirectoryPath = path?.appendingPathComponent("Background")
        let documentFolder = path?.appendingPathComponent("Documents/Background/AddColorBackgroundTest.pdf")
        
        // Copy file
        if let writeDirectoryPath = writeDirectoryPath {
            do {
                try FileManager.default.createDirectory(at: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
            } catch {
                print("Error creating directory: \(error)")
            }
            
            let writeFilePath = writeDirectoryPath.appendingPathComponent("DeleteBackgroundTest.pdf")
            
            if let documentFolder = documentFolder {
                do {
                    try FileManager.default.copyItem(at: documentFolder, to: writeFilePath)
                } catch {
                    print("Error copying file: \(error)")
                }
            }
            
            deleteBackgroundURL = writeFilePath
            
            if let document = CPDFDocument(url: deleteBackgroundURL) {
                if let pageBackground = document.background() {
                    pageBackground.clear()
                    document.write(to: deleteBackgroundURL)
                }
            }
        }
        
        commandLineStr += "Done. Results saved in AddImageBackgroundTest.pdf\n"
    }
    
    func getStringFromEnumVertalign(_ enums: Int) -> String {
        switch enums {
        case 0:
            return "top alignment"
        case 1:
            return "center alignment"
        case 2:
            return "bottom alignment"
        default:
            return " "
        }
    }
    
    func getStringFromEnumHorizalign(_ enums: Int) -> String {
        switch enums {
        case 0:
            return "left alignment"
        case 1:
            return "center alignment"
        case 2:
            return "right alignment"
        default:
            return " "
        }
    }
    
    func openFileWithURL(_ url: URL) {
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
