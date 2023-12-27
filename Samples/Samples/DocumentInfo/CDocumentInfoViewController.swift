//
//  CDocumentInfoViewController.swift
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
// The sample code illustrates how to create new bookmarks and use bookmark go to
// the page using API.
//-----------------------------------------------------------------------------------------

class CDocumentInfoViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to extract information about PDF documents, such as: author, date created.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        // Determine whether to export the document

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
    
    override func buttonItemClick_run(_ sender: Any) {
        if self.document != nil {
            self.isRun = false
            
            self.commandLineStr += "Running DocumentInfo sample...\n\n"
            self.printDocumentInfo(document)
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

    func printDocumentInfo(_ document: CPDFDocument?) {
        var documentInfo = "File Name: \(String(describing: document?.documentURL.lastPathComponent))\n"
        documentInfo += "File Szie: \(fileSizeStr())\n"
        documentInfo += "Title: \(document?.documentAttributes()[CPDFDocumentAttribute.titleAttribute] as? String ?? "")\n"
        documentInfo += "Author: \(document?.documentAttributes()[CPDFDocumentAttribute.authorAttribute] as? String ?? "")\n"
        documentInfo += "Subject: \(document?.documentAttributes()[CPDFDocumentAttribute.subjectAttribute] as? String ?? "")\n"
        documentInfo += "Keywords: \(document?.documentAttributes()[CPDFDocumentAttribute.keywordsAttribute] as? String ?? "")\n"
        
        let versionString = "\(String(describing: document?.majorVersion)).\(String(describing: document?.minorVersion))"
        documentInfo += "Version: \(versionString)\n"
        
        documentInfo += "Pages: \(String(describing: document?.pageCount))\n"
        documentInfo += "Creator: \(document?.documentAttributes()[CPDFDocumentAttribute.creatorAttribute] as? String ?? "")\n"
        
        if let creationDate = document?.documentAttributes()[CPDFDocumentAttribute.creationDateAttribute] as? Date {
            let dateFormatter = DateFormatter()
            dateFormatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
            let formattedDate = dateFormatter.string(from: creationDate)
            
            if formattedDate.count >= 16 {
                let startIndex = formattedDate.index(formattedDate.startIndex, offsetBy: 2)
                let endIndex = formattedDate.index(formattedDate.startIndex, offsetBy: 4)
                let year = formattedDate[startIndex..<endIndex]
                
                let startIndex2 = formattedDate.index(formattedDate.startIndex, offsetBy: 5)
                let endIndex2 = formattedDate.index(formattedDate.startIndex, offsetBy: 7)
                let month = formattedDate[startIndex2..<endIndex2]
                
                let startIndex3 = formattedDate.index(formattedDate.startIndex, offsetBy: 8)
                let endIndex3 = formattedDate.index(formattedDate.startIndex, offsetBy: 10)
                let day = formattedDate[startIndex3..<endIndex3]
                
                let startIndex4 = formattedDate.index(formattedDate.startIndex, offsetBy: 11)
                let endIndex4 = formattedDate.index(formattedDate.startIndex, offsetBy: 13)
                let hour = formattedDate[startIndex4..<endIndex4]
                
                let startIndex5 = formattedDate.index(formattedDate.startIndex, offsetBy: 14)
                let endIndex5 = formattedDate.index(formattedDate.startIndex, offsetBy: 16)
                let minutes = formattedDate[startIndex5..<endIndex5]
                
                self.commandLineStr += "Creation Date: \(year)-\(month)-\(day) \(hour):\(minutes)\n"
            }
        }
        
        if let creationDate = document?.documentAttributes()[CPDFDocumentAttribute.modificationDateAttribute] as? Date {
            let dateFormatter = DateFormatter()
            dateFormatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
            let formattedDate = dateFormatter.string(from: creationDate)
            
            if formattedDate.count >= 16 {
                let startIndex = formattedDate.index(formattedDate.startIndex, offsetBy: 2)
                let endIndex = formattedDate.index(formattedDate.startIndex, offsetBy: 4)
                let year = formattedDate[startIndex..<endIndex]
                
                let startIndex2 = formattedDate.index(formattedDate.startIndex, offsetBy: 5)
                let endIndex2 = formattedDate.index(formattedDate.startIndex, offsetBy: 7)
                let month = formattedDate[startIndex2..<endIndex2]
                
                let startIndex3 = formattedDate.index(formattedDate.startIndex, offsetBy: 8)
                let endIndex3 = formattedDate.index(formattedDate.startIndex, offsetBy: 10)
                let day = formattedDate[startIndex3..<endIndex3]
                
                let startIndex4 = formattedDate.index(formattedDate.startIndex, offsetBy: 11)
                let endIndex4 = formattedDate.index(formattedDate.startIndex, offsetBy: 13)
                let hour = formattedDate[startIndex4..<endIndex4]
                
                let startIndex5 = formattedDate.index(formattedDate.startIndex, offsetBy: 14)
                let endIndex5 = formattedDate.index(formattedDate.startIndex, offsetBy: 16)
                let minutes = formattedDate[startIndex5..<endIndex5]
                
                self.commandLineStr += "Modification Date: \(year)-\(month)-\(day) \(hour):\(minutes)\n"
            }
        }
        
        documentInfo += "Printing: \(document?.allowsPrinting == true ? "true" : "false")\n"
        documentInfo += "Content Copying: \(document?.allowsCopying == true ? "true" : "false")\n"
        documentInfo += "Document Change: \(document?.allowsDocumentChanges == true ? "true" : "false")\n"
        documentInfo += "Document Assembly: \(document?.allowsDocumentAssembly == true ? "true" : "false")\n"
        documentInfo += "Commenting: \(document?.allowsCommenting == true ? "true" : "false")\n"
        documentInfo += "Filling of Form Field: \(document?.allowsFormFieldEntry == true ? "true" : "false")\n"

        self.commandLineStr += documentInfo
    }

    func fileSizeStr() -> String {
        let defaultManager = FileManager.default
        let fileURL = self.document?.documentURL
        
        if !defaultManager.fileExists(atPath: fileURL?.path ?? "") {
            return ""
        }

        do {
            let attrib = try defaultManager.attributesOfItem(atPath: fileURL?.path ?? "")
            if let fileSize = attrib[.size] as? UInt64 {
                let fileSizeInKilobytes = Float(fileSize) / 1024.0
                let fileSizeInMegabytes = fileSizeInKilobytes / 1024.0
                let fileSizeInGigabytes = fileSizeInMegabytes / 1024.0

                if fileSizeInGigabytes >= 1.0 {
                    return String(format: "%.1fG", fileSizeInGigabytes)
                } else if fileSizeInMegabytes >= 1.0 {
                    return String(format: "%.1fM", fileSizeInMegabytes)
                } else {
                    return String(format: "%.1fK", fileSizeInKilobytes)
                }
            }
        } catch {
            print("Error: \(error)")
        }

        return ""
    }

}
