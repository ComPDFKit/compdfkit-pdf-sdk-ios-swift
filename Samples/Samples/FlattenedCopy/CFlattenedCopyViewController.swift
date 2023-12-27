//
//  CFlattenedCopyViewController.swift
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
// The sample code illustrates how do I create a copy of Flattened using API.
//-----------------------------------------------------------------------------------------

class CFlattenedCopyViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""
    var digitalSignatureURL:URL?
    var flattenedCopyURL:URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to create a copy of Flattened.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        if isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = openfileButton
                alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
            }
            
            let flattenedCopyAction = UIAlertAction(title: NSLocalizedString("   FlattenedCopyTest.pdf   ", comment: ""), style: .default) { (action) in
                // Open FlattenedCopyTest.pdf
                self.openFile()
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(flattenedCopyAction)
            alertController.addAction(cancelAction)
            
            present(alertController, animated: false, completion: nil)
        } else {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = openfileButton
                alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
            }
            
            let noFilesAction = UIAlertAction(title: NSLocalizedString("No files for this sample.", comment: ""), style: .default, handler: nil)
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(noFilesAction)
            alertController.addAction(cancelAction)
            
            present(alertController, animated: false, completion: nil)
        }
    }
    
    override func buttonItemClick_run(_ sender: Any) {
        if document != nil {
            self.isRun = true
            
            self.commandLineStr += "Running FlattenedCopy sample...\n\n"
            self.flattenedCopy(document)
            
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
    func flattenedCopy(_ oldDocument: CPDFDocument?) {
        // Get Sandbox path for saving the PDF File
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
        let writeDirectoryPath = path.appendingPathComponent("FlattenedCopy")

        do {
            try FileManager.default.createDirectory(at: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
            let writeFilePath = writeDirectoryPath.appendingPathComponent("FlattenedCopyTest.pdf")
            
            // Save the document in the test PDF file
            self.flattenedCopyURL = writeFilePath
            oldDocument?.write(to: self.flattenedCopyURL)
            
            // Create a new document for the test PDF file
            let document = CPDFDocument(url: self.flattenedCopyURL)
            
            // Save a flattened copy of the document
            document?.writeFlatten(to: self.flattenedCopyURL)
            
            self.commandLineStr += "Done. Results saved in FlattenedCopyTest.pdf\n"
        } catch {
            self.commandLineStr += "Error: \(error.localizedDescription)\n"
        }
    }

    func openFile() {
        if let flattenedCopyURL = self.flattenedCopyURL {
            let activityVC = UIActivityViewController(activityItems: [flattenedCopyURL], applicationActivities: nil)
            activityVC.definesPresentationContext = true
            if UIDevice.current.userInterfaceIdiom == .pad {
                activityVC.popoverPresentationController?.sourceView = self.openfileButton
                activityVC.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            
            present(activityVC, animated: true, completion: nil)
            
            activityVC.completionWithItemsHandler = { (activityType, completed, returnedItems, activityError) in
                if completed {
                    print("Success!")
                } else {
                    print("Failed or Canceled!")
                }
            }
        } else {
            print("Flattened copy URL is nil.")
        }
    }

}
