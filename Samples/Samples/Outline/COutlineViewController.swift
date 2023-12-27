//
//  COutlineViewController.swift
//  Samples
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

import UIKit
import ComPDFKit

//-----------------------------------------------------------------------------------------
// The sample code illustrates how to create outline and obtain document outline
// information using API.
//-----------------------------------------------------------------------------------------

class COutlineViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""
    var outlineURL:URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to create an outline and get existing outline information.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        if self.isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""),
                                                    message: "", preferredStyle: .alert)
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }

            let createOutlineAction = UIAlertAction(title: NSLocalizedString("CreateOutlineTest.pdf", comment: ""), style: .default) { [weak self] _ in
                self?.openFile()
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(createOutlineAction)
            alertController.addAction(cancelAction)

            present(alertController, animated: false, completion: nil)
        } else {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""),
                                                    message: "", preferredStyle: .alert)
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
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

            // Create bookmark and go to the page
            self.commandLineStr += "Running OutlineText sample...\n\n"
            self.createOutline(document)
            self.printOutline(document)
            self.commandLineStr += "\nDone!\n"
            self.commandLineStr += "-------------------------------------\n"
            self.commandLineTextView.text = self.commandLineStr
        } else {
            self.isRun = false
            self.commandLineStr += "The document is null, can't open..\n\n"
            self.commandLineTextView.text = self.commandLineStr
        }

    }
    
    // MARK: - Samples Methods
    func createOutline(_ oldDocument: CPDFDocument?) {
        // Get the Sandbox path for saving the PDF file
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/Outline")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath + "/CreateOutlineTest.pdf"
        
        // Save the document in the test PDF file
        self.outlineURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: self.outlineURL)
        
        // Create a new document for the test PDF file
        if let document = CPDFDocument(url: self.outlineURL) {
            // Create outline root
            document.setNewOutlineRoot()
            
            // Get the root from the PDF document
            if let outline = document.outlineRoot() {
                // Insert new outline nodes and set the outline titles
                let outlinePage1 = outline.insertChild(at: 0)
                outlinePage1?.label = "1. page1"
                
                let outlinePage2 = outline.insertChild(at: 1)
                outlinePage2?.label = "2. page2"
                
                let outlinePage3 = outline.insertChild(at: 2)
                outlinePage3?.label = "3. page3"
                
                let outlinePage4 = outline.insertChild(at: 3)
                outlinePage4?.label = "4. page4"
                
                let outlinePage5 = outline.insertChild(at: 4)
                outlinePage5?.label = "5. page5"
                
                // Insert secondary directory and set outline text
                let outlinePage1_1 = outlinePage1?.insertChild(at: 0)
                outlinePage1_1?.label = "1.1 page1_1"
                
                // Save the created outline action in the document
                document.write(to: self.outlineURL)
                
                self.commandLineStr += "Done.\n"
                self.commandLineStr += "Done. Results saved in CreateOutlineTest.pdf\n"
                
                // Refresh the document
                self.document = CPDFDocument(url: self.outlineURL)
            }
        }
    }
    
    // Print document outline information
    func printOutline(_ document: CPDFDocument?) {
        if let outline = document?.outlineRoot() {
            loadOutline(outline, level: 0)
        }
    }

    // Get subdirectory from root
    func loadOutline(_ outline: CPDFOutline, level: Int) {
        for i in 0..<outline.numberOfChildren {
            if let data = outline.child(at: i) {
                var destination: CPDFDestination? = data.destination

                if destination == nil {
                    if let action = data.action as? CPDFGoToAction {
                        destination = action.destination()
                    }
                }

                // The previous level directory will be one \t away from the previous level directory
                var intervalStr = ""
                for _ in 0..<level {
                    self.commandLineStr += "\t"
                }

                self.commandLineStr += intervalStr + "->" + data.label + "\n"
                loadOutline(data, level: level + 1)
            }
        }
    }

    func openFile() {
        if(self.outlineURL != nil) {
            let activityVC = UIActivityViewController(activityItems: [self.outlineURL!], applicationActivities: nil)
            activityVC.definesPresentationContext = true
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                activityVC.popoverPresentationController?.sourceView = self.openfileButton
                activityVC.popoverPresentationController?.sourceRect = self.openfileButton.bounds
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



}
