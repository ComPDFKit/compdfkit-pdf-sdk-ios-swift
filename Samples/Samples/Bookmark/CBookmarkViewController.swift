//
//  CBookmarkViewController.swift
//  Samples
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
///

import UIKit
import ComPDFKit

//-----------------------------------------------------------------------------------------
// The sample code illustrates how to create new bookmarks and use bookmark go to
// the page using API.
//-----------------------------------------------------------------------------------------

class CBookmarkViewController: CSamplesBaseViewController {
    
    var isRun: Bool = false
    var commandLineStr: String = ""
    var bookmarkURL: URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to create a new bookmark and implement a bookmark jump.", comment: "")
        
        self.commandLineTextView.text = ""
        self.isRun = false
        self.commandLineStr = ""
    }
    
    // MARK: - Action
    @IBAction override func buttonItemClick_openFile(_ sender: Any)  {
        if isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = openfileButton
                alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
            }
            
            let openFileAction = UIAlertAction(title: NSLocalizedString("CreateBookmarkTest.pdf", comment: ""), style: .default) { [weak self] _ in
                // Open CreateBookmarkTest.pdf
                self?.openFile()
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(openFileAction)
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
    
    @IBAction override func buttonItemClick_run(_ sender: Any)  {
        if(self.document != nil) {
            isRun = true
            
            self.commandLineStr = self.commandLineStr + "Running Bookmark sample...\n\n"
            self.createBookmark(document)
            self.commandLineStr = self.commandLineStr + "\nDone!\n"
            self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
            self.commandLineTextView.text = self.commandLineStr
        } else {
            isRun = false
            self.commandLineStr = self.commandLineStr + "The document is null, can't open..\n\n"
            self.commandLineTextView.text = self.commandLineStr
        }
    }

    // MARK: - Samples Methods
    func createBookmark(_ oldDocument: CPDFDocument?) {
        if(oldDocument == nil) {
            return
        }
        // Get Sandbox path for saving the PDF File
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
        let writeDirectoryPath = path.appendingPathComponent("Bookmark")
        
        do {
            try FileManager.default.createDirectory(at: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        } catch {
            print("Error creating directory: \(error)")
            return
        }
        
        let writeFilePath = writeDirectoryPath.appendingPathComponent("CreateBookmarkTest.pdf")
        
        // Save the document in the test PDF file
        bookmarkURL = writeFilePath
        oldDocument?.write(to: bookmarkURL)
        
        // Open the test PDF document
        let document = CPDFDocument(url: bookmarkURL)
        
        // Add bookmark
        document?.addBookmark("my bookmark", forPageIndex: 1)
        
        if let _ = document?.bookmark(forPageIndex: 1) {
            commandLineStr.append("Go to page 2\n")
        }
        
        // Save the add bookmark action in the document
        document?.write(to: bookmarkURL)
         
        commandLineStr.append("Done.\n")
        commandLineStr.append("Done. Results saved in CreateBookmarkTest.pdf\n")
    }
    
    func openFile() {
        if(bookmarkURL != nil) {
            let activityItems = [bookmarkURL!]
            let activityVC = UIActivityViewController(activityItems: activityItems, applicationActivities: nil)
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

}
