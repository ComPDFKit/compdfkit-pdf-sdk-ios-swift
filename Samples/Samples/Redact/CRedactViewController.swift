//
//  CRedactViewController.swift
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
// PDF Redactor is a separately licensable Add-on that offers options to remove
// (not just covering or obscuring) content within a region of PDF.
// With printed pages, redaction involves blacking-out or cutting-out areas of
// the printed page. With electronic documents that use formats such as PDF,
// redaction typically involves removing sensitive content within documents for
// safe distribution to courts, patent and government institutions, the media,
// customers, vendors or any other audience with restricted access to the content.
//-----------------------------------------------------------------------------------------

class CRedactViewController: CSamplesBaseViewController {
    var isRun = false
    var commandLineStr = ""
    var addRedactURL:URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to tag ciphertext and is a separate permissioned add-on that provides options to delete (not just overwrite or obscure) content within the PDF area. For a printed page, redaction involves removing or deleting certain areas of the printed page. For electronic documents that use formats such as PDF, redaction typically involves removing sensitive content from the document for safe distribution to courts, patent and government agencies, the media, customers, suppliers, or any other audience with restricted access to the content.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        // Determine whether to export the document
        if isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = openfileButton
                alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
            }
            
            let addRedactAction = UIAlertAction(title: NSLocalizedString("   AddRedactTest.pdf   ", comment: ""), style: .default) { [weak self] action in
                // Open AddRedactTest.pdf
                if let addRedactURL = self?.addRedactURL {
                    self?.openFile(url: addRedactURL)
                }
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(addRedactAction)
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
    
    override func buttonItemClick_run(_ sender: Any) {
        if document != nil {
            self.isRun = true
            
            self.commandLineStr += "Running Redact sample...\n\n"
            addRedact(document)
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
    func addRedact(_ oldDocument: CPDFDocument?) {
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory()
        let writeDirectoryPath = "\(path)/Documents/Redact"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = "\(writeDirectoryPath)/AddRedactTest.pdf"
        
        // Save the document in the test PDF file
        addRedactURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: addRedactURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: addRedactURL)
        let page = document?.page(at: 0)
        // Add redact
        if page != nil {
            let resultArray = document?.find("Page", with: .caseSensitive)
            
            // Get the first page of search results
            if let selections = resultArray?[3] {
                // Get the first search result on the first page
                if let selection = selections[0] as? CPDFSelection {
                    let redact = CPDFRedactAnnotation(document: document)
                    redact?.bounds = selection.bounds
                    redact?.setOverlayText("REDACTED")
                    redact?.setFont(UIFont.systemFont(ofSize: 12))
                    redact?.setFontColor(UIColor.red)
                    redact?.setAlignment(.left)
                    redact?.setInteriorColor(UIColor.black)
                    redact?.setBorderColor(UIColor.yellow)
                    page?.addAnnotation(redact)
                }
            }
            
            document?.write(to: addRedactURL)
        }
        
        commandLineStr += "The text need to be redact is: Page\(document?.index(for: page) ?? 0)\n"
        
        if let redact = document?.page(at: 0)?.annotations?.last as? CPDFRedactAnnotation {
            commandLineStr += "\tText in the redacted area is: \(Int(redact.bounds.origin.x)), \(Int(redact.bounds.origin.y)), \(Int(redact.bounds.size.width)), \(Int(redact.bounds.size.height))\n\n"
        }
        
        commandLineStr += "Done. Results saved in AddRedactTest.pdf\n"
    }

    func openFile(url: URL) {
        let activityVC = UIActivityViewController(activityItems: [url], applicationActivities: nil)
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
                    print("Failed Or Canceled!")
                }
            }
        }
    }



}
