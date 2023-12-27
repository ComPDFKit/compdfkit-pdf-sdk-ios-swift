//
//  CPDFToImageViewController.swift
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
// The sample code illustrates how to PDF to picture using API.
//-----------------------------------------------------------------------------------------

class CPDFToImageViewController: CSamplesBaseViewController {
    var isRun = false
    var commandLineStr = ""
    var imageFilePaths:[String] = []

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to convert PDF to image.", comment: "")
        
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
            
            for i in 0..<(self.document?.pageCount ?? 0) {
                let imageName = "PDFToImageTest\(i).png"
                let imageAction = UIAlertAction(title: NSLocalizedString(imageName, comment: ""), style: .default) { [weak self] (action) in
                    // Open PDFToImageTest.png
                    self?.openFile(self?.imageFilePaths[Int(i)] ?? "")
                }
                alertController.addAction(imageAction)
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            alertController.addAction(cancelAction)
            
            present(alertController, animated: false, completion: nil)
        } else {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
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
            self.isRun = true

            self.commandLineStr = self.commandLineStr + "Running Bookmark sample...\n\n"
            self.PDFToImage(document)
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
    // PDF to picture and save the picture
    func PDFToImage(_ document: CPDFDocument?) {
        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/PDFToImage")

        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }

        // Traverse the page, converting all pages to images
        for i in 0..<(document?.pageCount ?? 0) {
            // Get image from page
            let page = document?.page(at: i)
            guard let pageSize = document?.pageSize(at: i) else { continue }
            guard let image = page?.thumbnail(of: pageSize) else {
                continue
            }

            // Save image in Sandbox
            let imageFilePath = writeDirectoryPath.appending("/PDFToImageTest\(i).png")
            imageFilePaths.append(imageFilePath)
            
            if let imageData = image.jpegData(compressionQuality: 1.0) {
                do {
                    try imageData.write(to: NSURL.fileURL(withPath: imageFilePath))
                    commandLineStr += "Done.\n"
                    commandLineStr += "Done. Results saved in PDFToImageTest\(i).png\n"
                } catch {
                    commandLineStr += "Done.\n"
                    commandLineStr += "Done. Results saved in PDFToImageTest\(i).png fail !\n"
                }
            }
        }
    }

    // Open file
    func openFile(_ imageFilePath: String) {
        let activityVC = UIActivityViewController(activityItems: [URL(fileURLWithPath: imageFilePath)], applicationActivities: nil)
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
