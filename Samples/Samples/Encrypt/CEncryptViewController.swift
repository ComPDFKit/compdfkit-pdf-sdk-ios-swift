//
//  CEncryptViewController.swift
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
// The sample code illustrates how to encrypt and decrypt documents using API.
//-----------------------------------------------------------------------------------------

class CEncryptViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""
    var digitalSignatureURL:URL?
    var url:URL?
    var userPasswordURLs: [URL] = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.explainLabel.text = NSLocalizedString("This sample shows how to set user password and permission password, decrypt, set document permission.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        
        // Determine whether to export the document
        if self.isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            
            let encryptUserRC4Action = UIAlertAction(title: NSLocalizedString("   EncryptUserRC4Test.pdf   ", comment: ""), style: .default) { action in
                // Open EncryptUserRC4Test.pdf
                self.openFile(with: self.userPasswordURLs[0])
            }
            
            let encryptUserAES128Action = UIAlertAction(title: NSLocalizedString("   EncryptUserAES128Test.pdf   ", comment: ""), style: .default) { action in
                // Open EncryptUserAES128Test.pdf
                self.openFile(with: self.userPasswordURLs[1])
            }
            
            // Add more UIAlertAction handlers for other cases as needed
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(encryptUserRC4Action)
            alertController.addAction(encryptUserAES128Action)
            // Add more UIAlertAction instances for other cases as needed
            alertController.addAction(cancelAction)
            
            self.present(alertController, animated: false, completion: nil)
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
            
            self.present(alertController, animated: false, completion: nil)
        }
        
    }
    
    override func buttonItemClick_run(_ sender: Any) {
        if self.document != nil {
            self.isRun = true
            
            self.commandLineStr += "Running Bookmark sample...\n\n"
            encryptByUserPassword(document)
            encryptByOwnerPassword(document)
            encryptByAllPasswords(document)
            unlock()
            decrypt()
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
    func encryptByUserPassword(_ oldDocument: CPDFDocument?) {
        self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
        self.commandLineStr = self.commandLineStr + "Samples 1: Document use RC4 encrypt done\n"
        
        let path = NSHomeDirectory()
        let writeDirectoryPath = path + "/Documents/Encrypt"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath + "/EncryptUserRC4Test.pdf"
        let encryptUserRC4URL = URL(fileURLWithPath: writeFilePath)
        
        // Save the document in the test PDF file
        oldDocument?.write(to: encryptUserRC4URL)
        
        // Create a new document for test PDF file
        let document = CPDFDocument(url: encryptUserRC4URL)
        userPasswordURLs.append(encryptUserRC4URL)
    
        
        // Set encryption attributes
        let options: [CPDFDocumentWriteOption: Any] = [
            CPDFDocumentWriteOption.userPasswordOption: "User",
            CPDFDocumentWriteOption.encryptionLevelOption: NSNumber(value: 0)
        ]
        
        document?.write(to: encryptUserRC4URL, withOptions: options)
        
        commandLineStr += "User password is: User\n"
        commandLineStr += "Done. Results saved in EncryptUserRC4Test.pdf\n\n"
        
        
        self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
        self.commandLineStr = self.commandLineStr + "Samples 2: Document use AES128 encrypt done\n"
        
        let writeAES128TestPath = writeDirectoryPath + "/EncryptUserAES128Test.pdf"
        
        // Save the document in the test PDF file
        let encryptAES128UserRC4URL = URL(fileURLWithPath: writeAES128TestPath)
        document?.write(to: encryptAES128UserRC4URL)
        
        // Create a new document for test PDF file
        let AES128document = CPDFDocument(url: encryptAES128UserRC4URL)
        self.userPasswordURLs.append(encryptAES128UserRC4URL)
        
        //  Set encryption attributes
        let AES128options: [CPDFDocumentWriteOption: Any] = [
            CPDFDocumentWriteOption.userPasswordOption: "User",
            CPDFDocumentWriteOption.encryptionLevelOption: NSNumber(value: 1)
        ]
        AES128document?.write(to: encryptAES128UserRC4URL,withOptions: AES128options)
        
        commandLineStr += "User password is: User\n"
        commandLineStr += "Done. Results saved in EncryptUserAES128Test.pdf\n\n"
        
        self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
        self.commandLineStr = self.commandLineStr + "Samples 3: Document use AES256 encrypt done\n"
        
        let writeAES256TestPath = writeDirectoryPath + "/EncryptUserAES256Test.pdf"
        
        // Save the document in the test PDF file
        let encryptAES256UserRC4URL = URL(fileURLWithPath: writeAES256TestPath)
        document?.write(to: encryptAES256UserRC4URL)
        
        // Create a new document for test PDF file
        let AES256document = CPDFDocument(url: encryptAES256UserRC4URL)
        self.userPasswordURLs.append(encryptAES256UserRC4URL)
        
        //  Set encryption attributes
        let AES256options: [CPDFDocumentWriteOption: Any] = [
            CPDFDocumentWriteOption.userPasswordOption: "User",
            CPDFDocumentWriteOption.encryptionLevelOption: NSNumber(value: 2)
        ]
        AES256document?.write(to: encryptAES256UserRC4URL,withOptions: AES256options)
        
        commandLineStr += "User password is: User\n"
        commandLineStr += "Done. Results saved in EncryptUserAES256Test.pdf\n\n"
        
        commandLineStr += "User password is: User\n"
        commandLineStr += "Done. Results saved in EncryptUserAES128Test.pdf\n\n"
        
        self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
        self.commandLineStr = self.commandLineStr + "Samples 4: Document use NoEncryptAlgo encrypt done\n"
        
        let writeAlgoTestPath = writeDirectoryPath + "/EncryptUserNoEncryptAlgoTest.pdf"
        
        // Save the document in the test PDF file
        let encryptAlgoUserRC4URL = URL(fileURLWithPath: writeAES256TestPath)
        document?.write(to: encryptAlgoUserRC4URL)
        
        // Create a new document for test PDF file
        let Algodocument = CPDFDocument(url: encryptAlgoUserRC4URL)
        self.userPasswordURLs.append(encryptAlgoUserRC4URL)
        
        //  Set encryption attributes
        let Algooptions: [CPDFDocumentWriteOption: Any] = [
            CPDFDocumentWriteOption.userPasswordOption: "User",
            CPDFDocumentWriteOption.encryptionLevelOption: NSNumber(value: 3)
        ]
        Algodocument?.write(to: encryptAES256UserRC4URL,withOptions: Algooptions)
        
        commandLineStr += "User password is: User\n"
        commandLineStr += "Done. Results saved in EncryptUserNoEncryptAlgoTest.pdf\n\n"
    }
    
    func encryptByOwnerPassword(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 5: Encrypt by owner password done\n"
        
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = path + "/Encrypt"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = writeDirectoryPath + "/EncryptOwnerRC4Test.pdf"
        
        // Save the document in the test PDF file
        let encryptOwnerRC4URL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: encryptOwnerRC4URL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: encryptOwnerRC4URL)
        userPasswordURLs.append(encryptOwnerRC4URL)
        
        // Set encryption attributes
        let options: [CPDFDocumentWriteOption: Any] = [
            CPDFDocumentWriteOption.userPasswordOption: "User",
            CPDFDocumentWriteOption.ownerPasswordOption: "Owner",
            CPDFDocumentWriteOption.encryptionLevelOption: NSNumber(value: 0),
            CPDFDocumentWriteOption.allowsPrintingOption: false,
            CPDFDocumentWriteOption.allowsCopyingOption: false
        ]
        document?.write(to: encryptOwnerRC4URL, withOptions: options)
        
        commandLineStr += "Owner password is: Owner\n"
        commandLineStr += "Done. Results saved in EncryptOwnerRC4Test.pdf\n\n"
    }
    
    func encryptByAllPasswords(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 6: Encrypt by Both user and owner passwords done\n"
        
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = path + "/Encrypt"
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        let writeFilePath = "\(writeDirectoryPath)/EncryptAllAES256Test.pdf"
        
        // Save the document in the test PDF file
        let encryptAllAES256URL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: encryptAllAES256URL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: encryptAllAES256URL)
        userPasswordURLs.append(encryptAllAES256URL)
        
        // Set encryption attributes
        let options: [CPDFDocumentWriteOption: Any] = [
            CPDFDocumentWriteOption.ownerPasswordOption: "Owner",
            CPDFDocumentWriteOption.userPasswordOption: "User",
            CPDFDocumentWriteOption.encryptionLevelOption: NSNumber(value: 2),
            CPDFDocumentWriteOption.allowsPrintingOption: true,
            CPDFDocumentWriteOption.allowsHighQualityPrintingOption: false,
            CPDFDocumentWriteOption.allowsCopyingOption: false,
            CPDFDocumentWriteOption.allowsDocumentChangesOption: false,
            CPDFDocumentWriteOption.allowsDocumentAssemblyOption: false,
            CPDFDocumentWriteOption.allowsCommentingOption: false,
            CPDFDocumentWriteOption.allowsFormFieldEntryOption: false
        ]
        document?.write(to: encryptAllAES256URL, withOptions: options)
        
        commandLineStr += "User password is: User\n"
        commandLineStr += "Owner password is: Owner\n"
        commandLineStr += "Done. Results saved in EncryptAllAES256Test.pdf\n\n"
    }
    
    func unlock() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 7: Unlock with owner password and user password\n"
        
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = path + "/Encrypt"
        if let documentFolder = Bundle.main.path(forResource: "AllPasswords", ofType: "pdf") {
            // Copy file
            if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
                try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
            }
            let writeFilePath = "\(writeDirectoryPath)/unlockAllPasswords.pdf"
            
            if FileManager.default.fileExists(atPath: documentFolder) {
                try? FileManager.default.copyItem(at: URL(fileURLWithPath: documentFolder), to: URL(fileURLWithPath: writeFilePath))
            }
            
            // Unlock the document and print document permission information
            // It is worth noting that the document is only unlocked, not decrypted, and the password is still required for the next opening
            let unlockAllPasswordsURL = URL(fileURLWithPath: writeFilePath)
            if let document = CPDFDocument(url: unlockAllPasswordsURL) {
                document.unlock(withPassword: "Owner")
                
                commandLineStr += "AllowsPrinting: \(document.allowsPrinting ? "YES" :  "NO")\n"
                commandLineStr += "AllowsHighQualityPrinting: \(document.allowsHighQualityPrinting ? "YES" :  "NO")\n"
                commandLineStr += "AllowsCopying: \(document.allowsCopying ? "YES" :  "NO")\n"
                commandLineStr += "AllowsDocumentChanges: \(document.allowsDocumentChanges ? "YES" :  "NO")\n"
                commandLineStr += "AllowsDocumentAssembly: \(document.allowsDocumentAssembly ? "YES" :  "NO")\n"
                commandLineStr += "AllowsCommenting: \(document.allowsPrinting ? "YES" :  "NO")\n"
                commandLineStr += "AllowsFormFieldEntry: \(document.allowsFormFieldEntry ? "YES" :  "NO")\n\n"
            }
        }
    }
    
    func decrypt() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 8: Decrypt with owner password and user password\n"
        
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = path + "/Encrypt"
        if let documentFolder = Bundle.main.path(forResource: "AllPasswords", ofType: "pdf") {
            // Copy file
            if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
                try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
            }
            let writeFilePath = "\(writeDirectoryPath)/DecryptAllPasswordsTest.pdf"
            
            if FileManager.default.fileExists(atPath: documentFolder) {
                try? FileManager.default.copyItem(at: URL(fileURLWithPath: documentFolder), to: URL(fileURLWithPath: writeFilePath))
            }
            
            // Decrypt document
            let decryptAllPasswordsURL = URL(fileURLWithPath: writeFilePath)
            if let document = CPDFDocument(url: decryptAllPasswordsURL) {
                userPasswordURLs.append(decryptAllPasswordsURL)
                document.unlock(withPassword: "Owner")
                document.writeDecrypt(to: decryptAllPasswordsURL)
                
                commandLineStr += "Done. Results saved in DecryptAllPasswordsTest.pdf\n\n"
            }
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
