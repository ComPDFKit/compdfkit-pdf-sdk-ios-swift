//
//  CAnnotationImportExportViewController.swift
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
// The sample code illustrates how to import and export anntation using API
//-----------------------------------------------------------------------------------------

class CAnnotationImportExportViewController: CSamplesBaseViewController {
    
    var isRun: Bool = false
    var commandLineStr: String = ""
    var exportFilePath: String = ""
    var importURL: URL?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.explainLabel.text = NSLocalizedString("This sample shows how to set up the export and import of annotations. The document from which the annotations are exported is an xfdf file.", comment: "")
        self.commandLineTextView.text = ""
        self.isRun = false
        self.commandLineStr = ""
    }
    
    // MARK: - Action
    @IBAction override func buttonItemClick_openFile(_ sender: Any)  {
        // Determine whether to export the document
        if self.isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open…", comment: ""), message: "", preferredStyle: .alert)
            if UI_USER_INTERFACE_IDIOM() == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            let exportAction = UIAlertAction(title: NSLocalizedString("   ExportAnnotaiton.xfdf   ", comment: ""), style: .default) { (_) in
                // Open ExportAnnotaiton.pdf
                self.openFile(with: URL(fileURLWithPath: self.exportFilePath))
            }
            
            let importAction = UIAlertAction(title: NSLocalizedString("   ImportAnnotaitonTest.pdf   ", comment: ""), style: .default) { (_) in
                // Open ImportAnnotaitonTest.pdf
                if let importURL = self.importURL {
                    self.openFile(with: importURL)
                }
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(exportAction)
            alertController.addAction(importAction)
            alertController.addAction(cancelAction)
            
            self.present(alertController, animated: false, completion: nil)
        } else {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            if UI_USER_INTERFACE_IDIOM() == .pad {
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
            self.commandLineStr += "Running AnnotationImportExport sample...\n\n"
            exportAnnotaiton(document)
            importAnnotaiton()
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
    func importAnnotaiton() {
        let path = NSHomeDirectory().appending("/Documents")
        let writeDirectoryPath = path + "/AnnotationImportExport"
        let documentFolder = NSHomeDirectory().appending("/Documents" + "/Samples" + "/CommonFivePage.pdf")
        // Copy file
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = writeDirectoryPath + "/ImportAnnotaitonTest"
        
        if FileManager.default.fileExists(atPath: documentFolder) {
            try? FileManager.default.copyItem(at: URL(fileURLWithPath: documentFolder), to: URL(fileURLWithPath: writeFilePath))
        }
        
        let importDocument = CPDFDocument(url: URL(fileURLWithPath: documentFolder))
        importDocument?.importAnnotation(fromXFDFPath: self.exportFilePath)
        
        // Save the document in the PDF file
        self.importURL = URL(fileURLWithPath: writeFilePath)
        importDocument?.write(to: self.importURL)
        
        self.commandLineStr += "Done.\n"
        self.commandLineStr += "Done. Results saved in ImportAnnotaitonTest.pdf\n"
        
    }
    func exportAnnotaiton(_ document: CPDFDocument?) {
        let path = NSHomeDirectory().appending("/Documents")
        let writeDirectoryPath = path + "/AnnotationImportExport"
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        self.exportFilePath = writeDirectoryPath + "/ExportAnnotaiton.xfdf"
        
        document?.exportAnnotation(toXFDFPath: self.exportFilePath)
        
        self.commandLineStr += "Done.\n"
        self.commandLineStr += "Done. Results saved in ExportAnnotaiton.xfdf\n"
        
    }
    func openFile(with url: URL) {
        let activityVC = UIActivityViewController(activityItems: [url], applicationActivities: nil)
        activityVC.definesPresentationContext = true
        if UI_USER_INTERFACE_IDIOM() == .pad {
            activityVC.popoverPresentationController?.sourceView = self.openfileButton
            activityVC.popoverPresentationController?.sourceRect = self.openfileButton.bounds
        }
        
        present(activityVC, animated: true, completion: nil)
        
        activityVC.completionWithItemsHandler = { (activityType, completed, returnedItems, activityError) in
            if completed {
                print("Success!")
            } else {
                print("Failed Or Canceled!")
            }
        }
    }
    
}
