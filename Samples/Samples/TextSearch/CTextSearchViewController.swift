//
//  CTextSearchViewController.swift
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
// The sample shows how to use TextSearch to search text on PDF pages using regular
// expressions. TextSearch utility class bulids on functionality available in TextExtractor
// to simplify most common search operations
//-----------------------------------------------------------------------------------------

class CTextSearchViewController: CSamplesBaseViewController {
    var isRun = false
    var commandLineStr = ""
    var textSearchURL:URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample shows how to do a full document search and highlight for keywords", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    

    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        // Determine whether to export the document
          let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: nil, preferredStyle: .alert)
          
          if UIDevice.current.userInterfaceIdiom == .pad {
              alertController.popoverPresentationController?.sourceView = openfileButton
              alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
          }
          
          if isRun {
              let openAction = UIAlertAction(title: NSLocalizedString("TextSearchTest.pdf", comment: ""), style: .default) { [weak self] (action) in
                  // Open TextSearchTest.pdf
                  self?.openFile()
              }
              alertController.addAction(openAction)
          } else {
              let noFilesAction = UIAlertAction(title: NSLocalizedString("No files for this sample.", comment: ""), style: .default, handler: nil)
              alertController.addAction(noFilesAction)
          }
          
          let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
          alertController.addAction(cancelAction)
          
          present(alertController, animated: false, completion: nil)
    }
    
    override func buttonItemClick_run(_ sender: Any) {
        if  document != nil {
               self.isRun = true
               
               self.commandLineStr += "Running TextSearchTest sample...\n\n"
               searchText(oldDocument: document)
               self.commandLineStr += "\nDone!\n"
               self.commandLineStr += "-------------------------------------\n"
               
               // Refresh command line message
               self.commandLineTextView.text = self.commandLineStr
           } else {
               self.isRun = false
               self.commandLineStr += "The document is null, can't open..\n\n"
               self.commandLineTextView.text = self.commandLineStr
           }
    }
    
    // MARK: - Samples Methods
    func searchText(oldDocument: CPDFDocument?) {
        // Get Sandbox path for saving the PDFFile
        let path = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
        let writeDirectoryPath = path.appendingPathComponent("TextSearch")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath.path) {
            do {
                try FileManager.default.createDirectory(at: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
            } catch {
                print("Error creating directory: \(error)")
            }
        }
        
        let writeFilePath = writeDirectoryPath.appendingPathComponent("TextSearchTest.pdf")
        
        // Save the document in the test PDF file
        self.textSearchURL = writeFilePath
        oldDocument?.write(to: self.textSearchURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: self.textSearchURL)
        
        // Get array of search results
        let resultArray = document?.find("pdf")
        
        // Get the first page of search results
        if let selections = resultArray?.first as? [CPDFSelection], let selection = selections.first {
            self.commandLineStr += "The key 'PDF' has \(selections.count) results\n"
            
            // Set text highlighting
            var quadrilateralPoints: [NSValue] = []
            if let page = document?.page(at: 0) {
                let bounds = selection.bounds
                quadrilateralPoints.append(NSValue(cgPoint: CGPoint(x: bounds.minX, y: bounds.maxY)))
                quadrilateralPoints.append(NSValue(cgPoint: CGPoint(x: bounds.maxX, y: bounds.maxY)))
                quadrilateralPoints.append(NSValue(cgPoint: CGPoint(x: bounds.minX, y: bounds.minY)))
                quadrilateralPoints.append(NSValue(cgPoint: CGPoint(x: bounds.maxX, y: bounds.minY)))
                
                if let highlight = CPDFMarkupAnnotation(document: document, markupType: .highlight) {
                    highlight.color = UIColor.yellow
                    highlight.quadrilateralPoints = quadrilateralPoints
                    page.addAnnotation(highlight)
                }
            }
            
            // Save the text search action in the document
            document?.write(to: self.textSearchURL)
            self.commandLineStr += "Done.\n"
            self.commandLineStr += "Done. Results saved in TextSearchTest.pdf\n"
        }
    }
    
    func openFile() {
        if(self.textSearchURL != nil) {
            let activityItems: [Any] = [self.textSearchURL!]
            let activityVC = UIActivityViewController(activityItems: activityItems, applicationActivities: nil)
            activityVC.definesPresentationContext = true
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                if let sourceView = self.openfileButton {
                    activityVC.popoverPresentationController?.sourceView = sourceView
                    activityVC.popoverPresentationController?.sourceRect = sourceView.bounds
                }
            }
            
            self.present(activityVC, animated: true, completion: nil)
            
            activityVC.completionWithItemsHandler = { (activityType, completed, returnedItems, activityError) in
                if completed {
                    print("Success!")
                } else {
                    print("Failed Or Canceled!")
                }
            }
        }
    }



}
