//
//  CImageExtractViewController.swift
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
// The sample code illustrates how to extract all images from PDF documents
//-----------------------------------------------------------------------------------------

class CImageExtractViewController: CSamplesBaseViewController {
    var isRun = false
    var commandLineStr = ""
    var imageFilePaths:[String] = []
    var imageNames:[String] = []

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to extract all the images of a PDF document", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        func showOpenFileAlert() {
            if isRun {
                let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
                if UIDevice.current.userInterfaceIdiom == .pad {
                    alertController.popoverPresentationController?.sourceView = openfileButton
                    alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
                }

                for i in 0 ..< imageFilePaths.count {
                    let imageName = imageNames[i]
                    let imageAction = UIAlertAction(title: NSLocalizedString(imageName, comment: ""), style: .default) { [weak self] _ in
                        // Open ImageExtractTest.pdf
                        if let strongSelf = self {
                            strongSelf.openFile(imageFilePath: strongSelf.imageFilePaths[i])
                        }
                    }
                    alertController.addAction(imageAction)
                }

                let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
                alertController.addAction(cancelAction)

                present(alertController, animated: false, completion: nil)
            } else {
                let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
                if UIDevice.current.userInterfaceIdiom == .pad {
                    alertController.popoverPresentationController?.sourceView = openfileButton
                    alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
                }

                let noAction = UIAlertAction(title: NSLocalizedString("No files for this sample.", comment: ""), style: .default, handler: nil)
                let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)

                alertController.addAction(noAction)
                alertController.addAction(cancelAction)

                present(alertController, animated: false, completion: nil)
            }
        }

    }
    
    override func buttonItemClick_run(_ sender: Any) {
        if document != nil {
            isRun = true
            
            commandLineStr += "Running ImageExtract sample...\n\n"
            imageExtract(document: document)
            commandLineStr += "\nDone!\n"
            commandLineStr += "-------------------------------------\n"

            // Refresh command line message
            commandLineTextView.text = commandLineStr
        } else {
            isRun = false
            commandLineStr += "The document is null, can't open..\n\n"
            commandLineTextView.text = commandLineStr
        }
    }
    
    // MARK: - Samples Methods
    func imageExtract(document: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 1: Extract all images in the document\n"
        commandLineStr += "Opening the Samples PDF File\n"
        
        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory()
        let writeDirectoryPath = "\(path)/Documents/ImageExtract"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        // Extract all images from the document
        let pages = IndexSet(integersIn: Int(UInt(0))..<Int(document?.pageCount ?? 0))
        document?.extractImage(fromPages: pages, toPath: writeDirectoryPath)
        do {
            let fileManager = FileManager.default
            let fileArray = try fileManager.contentsOfDirectory(atPath: writeDirectoryPath)
            
            for fileName in fileArray {
                let filePath = writeDirectoryPath + "/" + fileName
                self.commandLineStr = self.commandLineStr + fileName + "\n"
                self.imageFilePaths.append(filePath)
                self.imageNames.append(fileName)
            }
        } catch {
            print("Error: \(error)")
        }

    }

    func openFile(imageFilePath: String) {
        let fileURL = URL(fileURLWithPath: imageFilePath)
        let activityVC = UIActivityViewController(activityItems: [fileURL], applicationActivities: nil)
        activityVC.definesPresentationContext = true
        
        if UIDevice.current.userInterfaceIdiom == .pad {
            activityVC.popoverPresentationController?.sourceView = openfileButton
            activityVC.popoverPresentationController?.sourceRect = openfileButton.bounds
        }
        
        present(activityVC, animated: true) {
            activityVC.completionWithItemsHandler = { activityType, completed, _, _ in
                if completed {
                    print("Success!")
                } else {
                    print("Failed or Canceled!")
                }
            }
        }
    }

}
