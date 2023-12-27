//
//  CPDFAViewController.swift
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
// The sample code illustrates how to convert PDF to PDFA format,
// including PDFA1a, PDFA1b using API.
//-----------------------------------------------------------------------------------------

class CPDFAViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""
    var convertToPDFA1aURL:URL?
    var convertToPDFA1bURL:URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to convert PDF to PDFA1a and PDFA1b formats.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""

    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        if self.isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            
            let convertToPDFA1aAction = UIAlertAction(title: NSLocalizedString("   ConvertToPDFA1aTest.pdf   ", comment: ""), style: .default) { _ in
                // Open ConvertToPDFA1aTest.pdf
                if let url = self.convertToPDFA1aURL {
                    self.openFile(with: url)
                }
            }
            
            let convertToPDFA1bAction = UIAlertAction(title: NSLocalizedString("   ConvertToPDFA1bTest.pdf   ", comment: ""), style: .default) { _ in
                // Open ConvertToPDFA1bTest.pdf
                if let url = self.convertToPDFA1bURL {
                    self.openFile(with:url)
                }
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(convertToPDFA1aAction)
            alertController.addAction(convertToPDFA1bAction)
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
            
            self.commandLineStr += "Running PDFA sample...\n\n"
            self.convertToPDFA1a(document)
            self.convertToPDFA1b(document)
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

    func convertToPDFA1a(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 1: Convert PDF to PDFA1a format\n"
        
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory().appending("/Documents")
        let writeDirectoryPath = path.appending("/PDFA")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath.appending("/ConvertToPDFA1aTest.pdf")
        
        // Save the document in the test PDF file
        convertToPDFA1aURL = NSURL.fileURL(withPath: writeFilePath)
        oldDocument?.write(to: convertToPDFA1aURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: convertToPDFA1aURL)
        
        // Save as PDFA1a format
        document?.writePDFA(to: convertToPDFA1aURL, with: .pdfa1a)
        
        commandLineStr += "Done. Results saved in ConvertToPDFA1aTest.pdf\n\n"
    }

    func convertToPDFA1b(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 2: Convert PDF to PDFA1b format\n"
        
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory().appending("/Documents")
        let writeDirectoryPath = path.appending("/PDFA")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath.appending("/ConvertToPDFA1bTest.pdf")
        
        // Save the document in the test PDF file
        convertToPDFA1bURL = NSURL.fileURL(withPath: writeFilePath)
        oldDocument?.write(to: convertToPDFA1bURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: convertToPDFA1bURL)
        
        // Save as PDFA1b format (Note: The provided Objective-C code has a mistake here, it specifies `CPDFTypePDFA1a` instead of `CPDFTypePDFA1b`)
        document?.writePDFA(to: convertToPDFA1bURL, with: .pdfa1b)
        
        commandLineStr += "Done. Results saved in ConvertToPDFA1bTest.pdf\n\n"
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
