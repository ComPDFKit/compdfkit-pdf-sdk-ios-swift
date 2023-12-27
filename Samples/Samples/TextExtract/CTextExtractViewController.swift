//
//  CTextExtractViewController.swift
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
// The sample code illustrates how to extract all text from PDF document using API.
//-----------------------------------------------------------------------------------------

class CTextExtractViewController: CSamplesBaseViewController {
    var isRun = false
    var commandLineStr = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to extract all the text of a PDF.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        // Determine whether to export the document
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
    
    override func buttonItemClick_run(_ sender: Any) {
        if document != nil {
            isRun = false
            
            commandLineStr += "Running Bookmark sample...\n\n"
            extractPageText(document)
            extractAllPageText(document)
            extractRectRangeText(document)
            commandLineStr += "-------------------------------------\n"
            
            // Refresh commandline message
            commandLineTextView.text = commandLineStr
        } else {
            isRun = false
            commandLineStr += "The document is null, can't open..\n\n"
            commandLineTextView.text = commandLineStr
        }
    }
    
    // MARK: - Samples Methods
    func extractPageText(_ document: CPDFDocument?) {
        commandLineStr += "Samples 1: Extract all text content in the specified page\n"
        commandLineStr += "Opening the Samples PDF File\n"
        commandLineStr += "The text content of the first page of the document:\n"
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Text:\n"
        
        let page = document?.page(at: 0)
        commandLineStr += "\(page?.string ?? "")\n"
        
        commandLineStr += "\nDone!\n"
    }

    func extractAllPageText(_ document: CPDFDocument?) {
        commandLineStr += "Samples 1: Extract all text content in the specified page\n"
        commandLineStr += "Opening the Samples PDF File\n"
        commandLineStr += "The text content of the first page of the document:\n"
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Text:\n"
        
        for i in 0..<(document?.pageCount ?? 0) {
            let page = document?.page(at: i)
            commandLineStr += "\(page?.string ?? "")\n"
        }
        
        commandLineStr += "\nDone!\n"
    }

    func extractRectRangeText(_ document: CPDFDocument?) {
        // Implement this method if needed
    }

}
