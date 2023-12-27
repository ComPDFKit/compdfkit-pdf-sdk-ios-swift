//
//  CBatesViewController.swift
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
// The sample code illustrates how to add and remove bates using API.
//-----------------------------------------------------------------------------------------

class CBatesViewController: CSamplesBaseViewController {
    
    var isRun: Bool = false
    var commandLineStr: String = ""
    var addCommonBatesURL: URL?
    var editBatesURL: URL?
    var deleteBatesURL: URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to add and remove bates codes.", comment: "")
        self.commandLineTextView.text = ""
        self.isRun = false
        self.commandLineStr = ""
    }
    
    
    // MARK: - Action
    @IBAction override func buttonItemClick_openFile(_ sender: Any)  {
        // Determine whether to export the document
        if isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = openfileButton
                alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
            }
            
            let addCommonBatesAction = UIAlertAction(title: NSLocalizedString("   AddCommonBatesTest.pdf   ", comment: ""), style: .default) { [weak self] _ in
                // Open AddCommonBatesTest.pdf\
                self?.openFile(with: self?.addCommonBatesURL)
            }
            let editBatesAction = UIAlertAction(title: NSLocalizedString("   EditBatesTest.pdf   ", comment: ""), style: .default) { [weak self] _ in
                // Open EditBatesTest.pdf
                self?.openFile(with:self?.editBatesURL)
            }
            let deleteBatesAction = UIAlertAction(title: NSLocalizedString("   DeleteBatesTest.pdf   ", comment: ""), style: .default) { [weak self] _ in
                // Open DeleteBatesTest.pdf
                self?.openFile(with:self?.deleteBatesURL)
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(addCommonBatesAction)
            alertController.addAction(editBatesAction)
            alertController.addAction(deleteBatesAction)
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
    
    @IBAction override func buttonItemClick_run(_ sender: Any)  {
        if  self.document != nil {
            self.isRun = true

            self.commandLineStr += "Running Bates sample...\n\n"
            self.addCommonBates(document)
            self.editBates()
            self.deleteBates()
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
    
    func addCommonBates(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 1: Insert common bates\n"

        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/Bates")

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
           try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true,attributes: nil)
        }

        let writeFilePath = writeDirectoryPath.appending("/AddCommonBatesTest.pdf")

        // Save the document in the test PDF file
        addCommonBatesURL = NSURL.fileURL(withPath: writeFilePath)
        oldDocument?.write(to: addCommonBatesURL)

        // Create a new document for the test PDF file
        let document = CPDFDocument(url: addCommonBatesURL)

        // Create common bates
        let bates = document?.bates()
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 0)
        bates?.setTextColor(UIColor.red, at: 0)
        bates?.setFontSize(14.0, at: 0)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 1)
        bates?.setTextColor(UIColor.red, at: 1)
        bates?.setFontSize(14.0, at: 1)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 2)
        bates?.setTextColor(UIColor.red, at: 2)
        bates?.setFontSize(14.0, at: 2)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 3)
        bates?.setTextColor(UIColor.red, at: 3)
        bates?.setFontSize(14.0, at: 3)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 4)
        bates?.setTextColor(UIColor.red, at: 4)
        bates?.setFontSize(14.0, at: 4)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 5)
        bates?.setTextColor(UIColor.red, at: 5)
        bates?.setFontSize(14.0, at: 5)
        bates?.pageString = "0-4"
        bates?.update()

        // Print bates message
        for i in 0..<6 {
            commandLineStr += "Text: " + (bates?.text(at: UInt(i)) ?? "") + "\n"
            commandLineStr += "Location: \(getStringFromEnumLocation(i))\n\n"
        }

        document?.write(to: addCommonBatesURL)

        commandLineStr += "Done. Results saved in AddCommonBatesTest.pdf\n"
    }

    func editBates() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 2: Edit common bates\n"
        
        // Save a document in Sandbox
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/Bates")
        let documentFolder = path.appending("/Documents/Bates/AddCommonBatesTest.pdf")
        
        // Copy file
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = writeDirectoryPath.appending("/EditBatesTest.pdf")
        
        if FileManager.default.fileExists(atPath: documentFolder) {
            try? FileManager.default.copyItem(atPath: documentFolder, toPath: writeFilePath)
        }
        
        editBatesURL = NSURL.fileURL(withPath: writeFilePath)
        let document = CPDFDocument(url: editBatesURL)
        
        // Edit bates message
        let bates = document?.bates()
        bates?.setText("<<#3#5#ComPDFKit-#-ComPDFKit>>", at: 0)
        bates?.setTextColor(UIColor.red, at: 0)
        bates?.setFontSize(14.0, at: 0)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 1)
        bates?.setTextColor(UIColor.red, at: 1)
        bates?.setFontSize(14.0, at: 1)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 2)
        bates?.setTextColor(UIColor.red, at: 2)
        bates?.setFontSize(14.0, at: 2)
        
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 3)
        bates?.setTextColor(UIColor.red, at: 3)
        bates?.setFontSize(14.0, at: 3)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 4)
        bates?.setTextColor(UIColor.red, at: 4)
        bates?.setFontSize(14.0, at: 4)
        bates?.setText("<<#3#5#Prefix-#-Suffix>>", at: 5)
        bates?.setTextColor(UIColor.red, at: 5)
        bates?.pageString = "0-4"
        bates?.update()
        
        for i in 0..<3 {
            commandLineStr += "Text: " + (bates?.text(at: UInt(i)) ?? "") + "\n"
            commandLineStr += "Location: \(getStringFromEnumLocation(i))\n\n"
        }
        
        document?.write(to: editBatesURL)
        
        commandLineStr += "Done. Results saved in EditBatesTest.pdf\n"
    }
    
    func deleteBates() {
        //     DeleteBatesTest

        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 3: Delete common bates\n"
        
        // Save a document in Sandbox
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/Bates")
        let documentFolder = path.appending("/Documents/Bates/AddCommonBatesTest.pdf")
        
        // Copy file
        do {
            try FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
            let writeFilePath = writeDirectoryPath.appending("DeleteBatesTest.pdf")
            try FileManager.default.copyItem(atPath: documentFolder, toPath: writeFilePath)
            deleteBatesURL = NSURL.fileURL(withPath: writeFilePath)
            let document = CPDFDocument(url: deleteBatesURL)
            
            if let bates = document?.bates() {
                bates.clear()
                document?.write(to: deleteBatesURL)
            }
            
            commandLineStr += "Done. Results saved in DeleteBatesTest.pdf\n"
        } catch {
            print("Error: \(error)")
        }
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
    
    func openFile(with url: URL?) {
        if(url != nil) {
            let activityItems = [url!]
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
