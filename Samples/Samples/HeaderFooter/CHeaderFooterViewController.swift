//
//  CHeaderFooterViewController.swift
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
// The sample code illustrates how to add and remove header footer using API.
//-----------------------------------------------------------------------------------------

class CHeaderFooterViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""
    var digitalSignatureURL:URL?
    var addCommonHeaderFooterURL:URL?
    var addPageHeaderFooterURL:URL?
    var editHeaderFooterURL:URL?
    var deleteHeaderFooterURL:URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to add and remove headers and footers.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        // Determine whether to export the document
        if self.isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: nil, preferredStyle: .alert)
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            
            let commonHeaderFooterAction = UIAlertAction(title: NSLocalizedString("   AddCommonHeaderFooterTest.pdf   ", comment: ""), style: .default) { (action) in
                // Open AddCommonHeaderFooterTest.pdf
                if let url = self.addCommonHeaderFooterURL {
                    self.openFileWithURL(url)
                }
            }
            let pageHeaderFooterAction = UIAlertAction(title: NSLocalizedString("   AddPageHeaderFooterTest.pdf   ", comment: ""), style: .default) { (action) in
                // Open AddPageHeaderFooterTest.pdf
                if let url = self.addPageHeaderFooterURL {
                    self.openFileWithURL(url)
                }
            }
            let editHeaderFooterAction = UIAlertAction(title: NSLocalizedString("   EditHeaderFooterTest.pdf   ", comment: ""), style: .default) { (action) in
                // Open EditHeaderFooterTest.pdf
                if let url = self.editHeaderFooterURL {
                    self.openFileWithURL(url)
                }
            }
            let deleteHeaderFooterAction = UIAlertAction(title: NSLocalizedString("   DeleteHeaderFooterTest.pdf   ", comment: ""), style: .default) { (action) in
                // Open DeleteHeaderFooterTest.pdf
                if let url = self.deleteHeaderFooterURL {
                    self.openFileWithURL(url)
                }
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(commonHeaderFooterAction)
            alertController.addAction(pageHeaderFooterAction)
            alertController.addAction(editHeaderFooterAction)
            alertController.addAction(deleteHeaderFooterAction)
            alertController.addAction(cancelAction)
            
            present(alertController, animated: false, completion: nil)
        } else {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: nil, preferredStyle: .alert)
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
            
            self.commandLineStr = self.commandLineStr + "Running HeaderFooter sample...\n\n"
            self.addCommonHeaderFooter(document)
            self.addPageHeaderFooter(document)
            self.editHeaderFooter()
            self.deleteHeaderFooter()
            
            self.commandLineStr = self.commandLineStr + "\nDone!\n"
            self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
            
            // Refresh commandline message
            self.commandLineTextView.text = self.commandLineStr
        } else {
            self.isRun = false
            self.commandLineStr = self.commandLineStr + "The document is null, can't open..\n\n"
            self.commandLineTextView.text = self.commandLineStr
        }
    }
    
    // MARK: - Samples Methods
    func addCommonHeaderFooter(_ oldDocument: CPDFDocument?) {
        self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
        self.commandLineStr = self.commandLineStr + "Samples 1: Insert common header footer\n"

        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/HeaderFooter")

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = writeDirectoryPath.appending("/AddCommonHeaderFooterTest.pdf")

        // Save the document in the test PDF file
        self.addCommonHeaderFooterURL = NSURL.fileURL(withPath: writeFilePath)
        oldDocument?.write(to: self.addCommonHeaderFooterURL)

        // Create a new document for the test PDF file
        let document = CPDFDocument(url: self.addCommonHeaderFooterURL)

        // Create text header footer
        if let headerFooter = document?.headerFooter() {
            headerFooter.setText("ComPDFKit", at: 0)
            headerFooter.setText("ComPDFKit", at: 1)
            headerFooter.setText("ComPDFKit", at: 2)
            headerFooter.setTextColor(UIColor.red, at: 0)
            headerFooter.setTextColor(UIColor.red, at: 1)
            headerFooter.setTextColor(UIColor.red, at: 2)
            headerFooter.setFontSize(14.0, at: 0)
            headerFooter.setFontSize(14.0, at: 1)
            headerFooter.setFontSize(14.0, at: 2)
            headerFooter.pageString = "0-4"

            headerFooter.update()

            // Print header footer object message
            for i in 0 ..< 3 {
                self.commandLineStr = self.commandLineStr + "Text: " + (headerFooter.text(at: UInt(i)) ?? "") + "\n"
                self.commandLineStr = self.commandLineStr + "Location: " + getStringFromEnumLocation(i) + "\n\n"
            }
        }

        document?.write(to: self.addCommonHeaderFooterURL)
        self.commandLineStr = self.commandLineStr + "Done. Results saved in AddCommonHeaderFooterTest.pdf\n"
    }

    func addPageHeaderFooter(_ oldDocument: CPDFDocument?) {
        self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
        self.commandLineStr = self.commandLineStr + "Samples 2: Insert page header footer\n"

        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/HeaderFooter")

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = writeDirectoryPath.appending("/AddPageHeaderFooterTest.pdf")

        // Save the document in the test PDF file
        self.addPageHeaderFooterURL = NSURL.fileURL(withPath: writeFilePath)
        oldDocument?.write(to: self.addPageHeaderFooterURL)

        // Create a new document for the test PDF file
        let document = CPDFDocument(url: self.addPageHeaderFooterURL)

        // Create page header footer
        if let headerFooter = document?.headerFooter() {
            headerFooter.setText("<<1,2>>", at: 0)
            headerFooter.setText("<<1,2>>", at: 1)
            headerFooter.setText("<<1,2>>", at: 2)
            headerFooter.setTextColor(UIColor.red, at: 0)
            headerFooter.setTextColor(UIColor.red, at: 1)
            headerFooter.setTextColor(UIColor.red, at: 2)
            headerFooter.setFontSize(14.0, at: 0)
            headerFooter.setFontSize(14.0, at: 1)
            headerFooter.setFontSize(14.0, at: 2)
            headerFooter.pageString = "0-4"

            headerFooter.update()

            // Print page header footer message
            for i in 0 ..< 3 {
                self.commandLineStr = self.commandLineStr + "Text: " + (headerFooter.text(at: UInt(i)) ?? "") + "\n"
                self.commandLineStr = self.commandLineStr + "Location: " + getStringFromEnumLocation(i) + "\n\n"
            }
        }

        document?.write(to: self.addPageHeaderFooterURL)
        self.commandLineStr = self.commandLineStr + "Done. Results saved in AddPageHeaderFooterTest.pdf\n"
    }
    
    func editHeaderFooter() {
        self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
        self.commandLineStr = self.commandLineStr + "Samples 3: Edit header footer\n"

        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/HeaderFooter")
        let documentFolder = path.appending("/Documents/HeaderFooter/AddCommonHeaderFooterTest.pdf")

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = writeDirectoryPath.appending("/EditHeaderFooterTest.pdf")

        // Copy file
        if FileManager.default.fileExists(atPath: documentFolder) {
            try? FileManager.default.copyItem(atPath: documentFolder, toPath: writeFilePath)
        }

        // Edit text header footer
        self.editHeaderFooterURL = NSURL.fileURL(withPath: writeFilePath)
        let document = CPDFDocument(url: self.editHeaderFooterURL)

        if let headerFooter = document?.headerFooter() {
            headerFooter.setText("ComPDFKit Samples", at: 0)
            headerFooter.setText("ComPDFKit", at: 1)
            headerFooter.setText("ComPDFKit", at: 2)
            headerFooter.update()

            // Print header footer object message
            for i in 0 ..< 3 {
                self.commandLineStr = self.commandLineStr + "Text: " + (headerFooter.text(at: UInt(i)) ?? "") + "\n"
                self.commandLineStr = self.commandLineStr + "Location: " + getStringFromEnumLocation(i) + "\n\n"
            }
        }

        document?.write(to: self.editHeaderFooterURL)
        self.commandLineStr = self.commandLineStr + "Done. Results saved in EditHeaderFooterTest.pdf\n"
    }

    func deleteHeaderFooter() {
        self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
        self.commandLineStr = self.commandLineStr + "Samples 4: Delete header footer\n"

        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/HeaderFooter")
        let documentFolder = path.appending("/Documents/HeaderFooter/AddCommonHeaderFooterTest.pdf")

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = writeDirectoryPath.appending("/DeleteHeaderFooterTest.pdf")

        // Copy file
        if FileManager.default.fileExists(atPath: documentFolder) {
            try? FileManager.default.copyItem(atPath: documentFolder, toPath: writeFilePath)
        }

        self.deleteHeaderFooterURL = NSURL.fileURL(withPath: writeFilePath)
        let document = CPDFDocument(url: self.deleteHeaderFooterURL)

        // Delete header footer
        if let headerFooter = document?.headerFooter() {
            headerFooter.clear()
        }

        document?.write(to: self.deleteHeaderFooterURL)
        self.commandLineStr = self.commandLineStr + "Done. Results saved in DeleteHeaderFooterTest.pdf\n"
    }
    
    func getStringFromEnumLocation(_ enums: Int) -> String {
        switch enums {
        case 0:
            return "Top Left"
        case 1:
            return "Top Middle"
        case 2:
            return "Top Right"
        case 3:
            return "Bottom Left"
        case 4:
            return "Bottom Middle"
        case 5:
            return "Bottom Right"
        default:
            return " "
        }
    }

    func openFileWithURL(_ url: URL) {
        let activityVC = UIActivityViewController(activityItems: [url], applicationActivities: nil)
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
