//
//  CPDFPageViewController.swift
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
// The sample code illustrates how to operate multiple pages of pdf document, including
// insert blank page, insert PDF document page, split page, merge page, delete page,
// rotate page, replace document page and export document page.
//-----------------------------------------------------------------------------------------

class CPDFPageViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""
    var insertBlankPageURL:URL?
    var insertPDFPageURL:URL?
    var mergePageURL:URL?
    var removePageURL:URL?
    var rotatePageURL:URL?
    var replacePageURL:URL?
    var extractPageURL:URL?
    var splitFilePaths:[String] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to print form list information, set up interactive forms (including text, checkbox, radioButton, button, list, Combox, and sign forms, delete forms), and fill out form information.", comment: "")
        
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
            
            let insertBlankAction = UIAlertAction(title: NSLocalizedString("InsertBlankPage.pdf", comment: ""), style: .default) { [unowned self] _ in
                // Open InsertBlankPage.pdf
                if let url = self.insertBlankPageURL {
                    openFile(with: url)
                }
            }
            alertController.addAction(insertBlankAction)
            
            let insertPDFAction = UIAlertAction(title: NSLocalizedString("InsertPDFPage.pdf", comment: ""), style: .default) { [unowned self] _ in
                // Open InsertPDFPage.pdf
                if let url = self.insertPDFPageURL {
                    openFile(with: url)
                }
            }
            alertController.addAction(insertPDFAction)
            
            for i in 0..<splitFilePaths.count {
                let imageName = "CommonFivePageSplitPage\(i).pdf"
                let imageAction = UIAlertAction(title: NSLocalizedString(imageName, comment: ""), style: .default) { [unowned self] _ in
                    // Open CommonFivePageSplitPage.pdf
                    openFile(with: URL(fileURLWithPath: splitFilePaths[i]))
                }
                alertController.addAction(imageAction)
            }
            
            let mergeAction = UIAlertAction(title: NSLocalizedString("MergePage.pdf", comment: ""), style: .default) { [unowned self] _ in
                // Open MergePage.pdf
                if let url = mergePageURL {
                    openFile(with: url)
                }
            }
            alertController.addAction(mergeAction)
            
            let removePagesAction = UIAlertAction(title: NSLocalizedString("RemovePages.pdf", comment: ""), style: .default) { [unowned self] _ in
                // Open RemovePages.pdf
                if let url = removePageURL {
                    openFile(with: url)
                }
            }
            alertController.addAction(removePagesAction)
            
            let rotatePagesAction = UIAlertAction(title: NSLocalizedString("RotatePage.pdf", comment: ""), style: .default) { [unowned self] _ in
                // Open RotatePage.pdf
                if let url = rotatePageURL {
                    openFile(with: url)
                }
            }
            alertController.addAction(rotatePagesAction)
            
            let replacePagesAction = UIAlertAction(title: NSLocalizedString("ReplacePages.pdf", comment: ""), style: .default) { [unowned self] _ in
                // Open ReplacePages.pdf
                if let url = replacePageURL {
                    openFile(with: url)
                }
            }
            alertController.addAction(replacePagesAction)
            
            let extractPagesAction = UIAlertAction(title: NSLocalizedString("ExtractPages.pdf", comment: ""), style: .default) { [unowned self] _ in
                // Open ExtractPages.pdf
                if let url = extractPageURL {
                    openFile(with: url)
                }
            }
            alertController.addAction(extractPagesAction)
            
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
            alertController.addAction(noAction)
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            alertController.addAction(cancelAction)
            
            present(alertController, animated: false, completion: nil)
        }
    }
    
    override func buttonItemClick_run(_ sender: Any) {
        if document != nil {
            isRun = true
            
            commandLineStr += "Running PDFPage sample...\n\n"
            insertBlankPage(document)
            insertPDFPage(document)
            splitPages(document)
            mergePages(document)
            deletePages(document)
            rotatePages(document)
            replacePages(document)
            extractPages(document)
            
            commandLineStr += "\nDone!\n"
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
    func insertBlankPage(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 1: Insert a blank A4-sized page into the sample document\n"
        commandLineStr += "Opening the Samples PDF File\n"

        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = "\(path)/PDFPage"

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = "\(writeDirectoryPath)/InsertBlankPage.pdf"

        // Save the document in the test PDF file
        insertBlankPageURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: insertBlankPageURL)

        // Create a new document for the test PDF file
        guard let document = CPDFDocument(url: insertBlankPageURL) else {
            return
        }

        // Insert blank page
        document.insertPage(CGSize(width: 595, height: 842), at: 1)

        // Save the created insert a blank PDF page action in the document
        document.write(to: insertBlankPageURL)

        commandLineStr += "Insert PageIndex : 1\n"
        commandLineStr += "Size : 595*842\n"
        commandLineStr += "Done. Results saved in InsertBlankPage.pdf\n"
    }

    func insertPDFPage(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 2: Import pages from another document into the example document\n"
        commandLineStr += "Opening the Samples PDF File\n"

        // Get the PDF document
        guard let filePathTest = Bundle.main.path(forResource: "text", ofType: "pdf") else {
            return
        }
        guard let insertDocument = CPDFDocument(url: URL(fileURLWithPath: filePathTest)) else {
            return
        }
        commandLineStr += "Open the document to be imported\n"

        let indexSet = NSMutableIndexSet()
        indexSet.add(0)

        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = "\(path)/PDFPage"

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = "\(writeDirectoryPath)/InsertPDFPage.pdf"

        // Save the document in the test PDF file
        insertPDFPageURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: insertPDFPageURL)

        // Create a new document for the test PDF file
        guard let document = CPDFDocument(url: insertPDFPageURL) else {
            return
        }

        // Insert PDF document
        document.importPages(indexSet as IndexSet, from: insertDocument, at: 1)

        // Save the created insert PDF document action in the document
        document.write(to: insertPDFPageURL)

        commandLineStr += "Done. Results saved in InsertPDFPage.pdf\n"
    }
    
    func splitPages(_ document: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 3: Split a PDF document into multiple pages\n"
        commandLineStr += "Opening the Samples PDF File\n"

        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = "\(path)/PDFPage"

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        
        for i in 0 ..< (document?.pageCount ?? 0) {
            var splitDocument: CPDFDocument?
            let index = IndexSet(integer: IndexSet.Element(i))
            
            let writeFilePath = "\(writeDirectoryPath)/CommonFivePageSplitPage\(i).pdf"
            
            splitFilePaths.append(writeFilePath)
            
            splitDocument = CPDFDocument()
            splitDocument?.importPages(index, from: document, at: 0)
             splitDocument?.write(to: URL(fileURLWithPath: writeFilePath))
            
            commandLineStr += "Done. Results saved in CommonFivePageSplitPage\(i).pdf\n"
        }
    }

    func mergePages(_ document: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 4: Merge split documents\n"
        
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = "\(path)/PDFPage"
        let writeFilePath = "\(writeDirectoryPath)/MergePages.pdf"
        
        let mergeDocument = CPDFDocument()
        
        // Copy file
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        
        for i in 0 ..< splitFilePaths.count {
            if let document = CPDFDocument(url: URL(fileURLWithPath: splitFilePaths[i]) ) {
                commandLineStr += "Opening CommonFivePageSplitPage\(i).pdf\n"
                let index = IndexSet(integer: 0)
                mergeDocument?.importPages(index, from: document, at: UInt(i))
            }
        }
        
        mergePageURL = URL(fileURLWithPath: writeFilePath)
        mergeDocument?.write(to: mergePageURL)
        
        commandLineStr += "Done. Results saved in MergePages.pdf\n"
    }

    // Delete page
    func deletePages(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 5: Delete the specified page of the document\n"
        commandLineStr += "Opening the Samples PDF File\n"
        
        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = "\(path)/PDFPage"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = "\(writeDirectoryPath)/RemovePages.pdf"
        
        // Save the document in the test PDF file
        removePageURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: removePageURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: removePageURL)
        
        // Delete even-numbered pages of a document
        var indexSet = IndexSet()
        for i in stride(from: 1, to: document?.pageCount ?? 0, by: 2) {
            indexSet.insert(IndexSet.Element(i))
        }
        
        document?.removePage(at: indexSet)
        
        // Save the delete even-numbered pages of a document action in the document
         document?.write(to: removePageURL)
        
        commandLineStr += "Done. Results saved in RemovePages.pdf\n"
    }

    // Rotate page
    func rotatePages(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 6: Rotate document pages\n"
        commandLineStr += "Opening the Samples PDF File\n"
        
        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = "\(path)/PDFPage"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = "\(writeDirectoryPath)/RotatePage.pdf"
        
        // Create a new document for the test PDF file
        rotatePageURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: rotatePageURL)
        
        // Create a new document for the test PDF file
        if let document = CPDFDocument(url: rotatePageURL) {
            // Rotate the first page 90 degrees
            if let page = document.page(at: 0) {
                page.rotation += 90
            }
            
            // Save the rotate page action in the document
            document.write(to: rotatePageURL)
            
            commandLineStr += "Done. Results saved in RotatePage.pdf\n"
        }
    }
    
    // Replace document page
    func replacePages(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 7: Replace specified pages of example documentation with other documentation specified pages\n"
        commandLineStr += "Opening the Samples PDF File\n"
        
        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = "\(path)/PDFPage"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = "\(writeDirectoryPath)/ReplacePages.pdf"
        
        // Save the document in the test PDF file
        replacePageURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: replacePageURL)
        
        // Create a new document for the test PDF file
        if let document = CPDFDocument(url: replacePageURL) {
            // Get PDF document
            if let filePathTest = Bundle.main.path(forResource: "text", ofType: "pdf"),
               let insertDocument = CPDFDocument(url: URL(fileURLWithPath: filePathTest)) {
                
                // Replace PDF document
                let insertSet = IndexSet(integer: 0)
                let removeSet = IndexSet(integer: 1)
                document.removePage(at: removeSet)
                document.importPages(insertSet, from: insertDocument, at: 1)
                
                // Save the replace pages action in the document
               document.write(to: replacePageURL)
            }
            
            commandLineStr += "Done. Results saved in ReplacePages.pdf\n"
        }
    }

    // Export document page
    func extractPages(_ document: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 8: Extract specific pages of a document\n"
        commandLineStr += "Opening the Samples PDF File\n"
        
        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = "\(path)/PDFPage"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = "\(writeDirectoryPath)/ExtractPages.pdf"
        
        // Get range of extract pages
        var indexSet = IndexSet()
        indexSet.insert(0)
        indexSet.insert(1)
        
        extractPageURL = URL(fileURLWithPath: writeFilePath)
        
        if let extractDocument = CPDFDocument() {
            extractDocument.importPages(indexSet, from: document, at: 0)
            
            // Save the extract pages action in the document
            extractDocument.write(to: extractPageURL)
            
            commandLineStr += "Done. Results saved in ExtractPages.pdf\n"
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
