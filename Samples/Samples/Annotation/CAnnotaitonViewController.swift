//
//  CAnnotaitonViewController.swift
//  Samples
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.


import UIKit
import ComPDFKit

//-----------------------------------------------------------------------------------------
// The sample code illustrates how to create new annotation and delete anntation,
// get anntation information list using API.
//-----------------------------------------------------------------------------------------

class CAnnotaitonViewController: CSamplesBaseViewController {
    
    var isRun: Bool = false
    var commandLineStr: String = ""
    var annotationURL: URL?
    var deleteAnnotationURL: URL?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        explainLabel.text = NSLocalizedString("This sample shows how to print the annotation list information, set the annotations (including markup, note, ink, freetext, circle, square, line, stamp, and sound annotations), and delete the annotations.", comment: "")
        
        commandLineTextView.text = ""
        isRun = false
    }
    
    // MARK: - Action
    @IBAction override func buttonItemClick_openFile(_ sender: Any) {
        if self.isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open…", comment: ""), message: "", preferredStyle: .alert)
            if UI_USER_INTERFACE_IDIOM() == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            let createAnnotationAction = UIAlertAction(title: NSLocalizedString("     CreateAnnotationTest.pdf      ", comment: ""), style: .default) { (action) in
                // Open CreateAnnotationTest.pdf
                self.openFile(with: self.annotationURL)
            }
            
            let deleteAnnotationAction = UIAlertAction(title: NSLocalizedString("     DeleteAnnotationTest.pdf      ", comment: ""), style: .default) { (action) in
                // Open DeleteAnnotationTest.pdf
                self.openFile(with: self.deleteAnnotationURL)
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(createAnnotationAction)
            alertController.addAction(deleteAnnotationAction)
            alertController.addAction(cancelAction)
            
            present(alertController, animated: false, completion: nil)
            
        } else {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open…", comment: ""), message: "", preferredStyle: .alert)
            if UI_USER_INTERFACE_IDIOM() == .pad {
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
    
    @IBAction override func buttonItemClick_run(_ sender: Any) {
        if self.document != nil {
            self.isRun = true
            
            // Create bookmark and go to the page
            commandLineStr += "Running CreateAnnotationTest sample...\n\n"
            
            createTestAnnots(self.document)
            
            printAnnotationList(self.document)
            
            deleteTestAnnot(self.document)
            
            commandLineStr += "\nDone!\n"
            commandLineStr += "-------------------------------------\n"
            self.commandLineTextView.text = self.commandLineStr
        } else {
            self.isRun = false
            commandLineStr += "The document is null, can't open..\n\n"
            commandLineTextView.text = commandLineStr
        }
    }
    
    // MARK: - Samples Methods
    func createTestAnnots(_ oldDocument: CPDFDocument?) {
        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory().appending("/Documents")
        let writeDirectoryPath = path + "/Annoation"
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath + "/CreateAnnotationTest.pdf"
        
        // Save the document in the test PDF file
        annotationURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: annotationURL)
        
        let document = CPDFDocument(url: annotationURL)
        //-----------------------------------------------------------------------------------------
        // Test of a free text annotation and ink annotation.
        
        let page1 = document?.page(at: 0)
        
        if page1 != nil {
            // Create a freetext annotation
            let freeText1 = CPDFFreeTextAnnotation(document: document)
            freeText1?.contents = "\n\nSome swift brown fox snatched a gray hare out of the air by freezing it with an angry glare."
            + "\n\nAha!\n\nAnd there was much rejoicing!"
            freeText1?.bounds = CGRect(x: 10, y: 200, width: 160, height: 570)
            freeText1?.font = UIFont(name: "Helvetica", size: 12)
            freeText1?.fontColor = UIColor.red
            freeText1?.alignment = .left
            // Add a freetext annotation for page
            page1?.addAnnotation(freeText1)
            
            // Create a ink annotation
            let ink = CPDFInkAnnotation(document: document)
            let startPoint = CGPoint(x: 220, y: 505)
            let point1 = CGPoint(x: 100, y: 490)
            let point2 = CGPoint(x: 120, y: 410)
            let point3 = CGPoint(x: 100, y: 400)
            let point4 = CGPoint(x: 180, y: 490)
            let endPoint = CGPoint(x: 140, y: 440)
            ink?.color = UIColor.red
            ink?.opacity = 0.5
            ink?.borderWidth = 2.0
            ink?.paths = [[startPoint, point1, point2, point3, point4, endPoint]]
            page1?.addAnnotation(ink)
            
        }
        
        //-----------------------------------------------------------------------------------------
        // Test of line annotation
        // Set line width and dotted line
        let border1 = CPDFBorder(style: .dashed, lineWidth: 1, dashPattern: [2, 1])
        let border2 = CPDFBorder(style: .dashed, lineWidth: 1, dashPattern: [2, 0])
        let page2 = document?.page(at: 1)
        
        // Create a Line annotation
        let line1 = CPDFLineAnnotation(document: document)
        line1?.startPoint = CGPoint(x: 350, y: 270)
        line1?.endPoint = CGPoint(x: 260, y: 370)
        line1?.startLineStyle = .square
        line1?.endLineStyle = .circle
        line1?.color = UIColor.red
        line1?.interiorColor = UIColor.yellow
        line1?.opacity = 0.5
        line1?.interiorOpacity = 0.5
        line1?.border = border1
        line1?.contents = "Dashed Captioned"
        page2?.addAnnotation(line1)
        
        let line2 = CPDFLineAnnotation(document: document)
        line2?.startPoint = CGPoint(x: 385, y: 480)
        line2?.endPoint = CGPoint(x: 540, y: 555)
        line2?.startLineStyle = .circle
        line2?.endLineStyle = .openArrow
        line2?.color = UIColor.red
        line2?.interiorColor = UIColor.yellow
        line2?.opacity = 0.5
        line2?.interiorOpacity = 0.5
        line2?.border = border2
        line2?.contents = "Inline Caption"
        page2?.addAnnotation(line2)
        
        let line3 = CPDFLineAnnotation(document: document)
        line3?.startPoint = CGPoint(x: 25, y: 426)
        line3?.endPoint = CGPoint(x: 180, y: 555)
        line3?.startLineStyle = .circle
        line3?.endLineStyle = .square
        line3?.color = UIColor.green
        line3?.interiorColor = UIColor.yellow
        line3?.opacity = 0.5
        line3?.interiorOpacity = 0.5
        line3?.border = border2
        line3?.contents = "Offset Caption"
        page2?.addAnnotation(line3)
        
        //-----------------------------------------------------------------------------------------
        // Test of circle and square annotation
        let page3 = document?.page(at: 2)
        
        let circle1 = CPDFCircleAnnotation(document: document)
        circle1?.bounds = CGRect(x: 300, y: 300, width: 100, height: 100)
        circle1?.color = UIColor.red
        circle1?.interiorColor = UIColor.yellow
        circle1?.opacity = 0.5
        circle1?.interiorOpacity = 0.5
        circle1?.border = border1
        page3?.addAnnotation(circle1)
        
        let circle2 = CPDFCircleAnnotation(document: document)
        circle2?.bounds = CGRect(x: 100, y: 100, width: 200, height: 200)
        circle2?.color = UIColor.green
        circle2?.interiorColor = UIColor.purple
        circle2?.opacity = 1.0
        circle2?.interiorOpacity = 1.0
        circle2?.border = border2
        page3?.addAnnotation(circle2)
        
        let square1 = CPDFSquareAnnotation(document: document)
        square1?.bounds = CGRect(x: 10, y: 200, width: 80, height: 150)
        square1?.color = UIColor.red
        square1?.interiorColor = UIColor.yellow
        square1?.opacity = 0.5
        square1?.interiorOpacity = 0.5
        square1?.border = border1
        page3?.addAnnotation(square1)
        
        let square2 = CPDFSquareAnnotation(document: document)
        square2?.bounds = CGRect(x: 400, y: 200, width: 80, height: 300)
        square2?.color = UIColor.green
        square2?.interiorColor = UIColor.purple
        square2?.opacity = 1.0
        square2?.interiorOpacity = 1.0
        square2?.border = border2
        page3?.addAnnotation(square2)
        
        //-----------------------------------------------------------------------------------------
        // Test of circle and square annotation
        let page4 = document?.page(at: 3)
        
        let resultArray = document?.find("page", with:CPDFSearchOptions(rawValue: 0))
        
        // Get the first page of search results
        if let selections = resultArray?.last{
            // Get the first search result on the first page
            if let selection = selections.first {
                var quadrilateralPoints = [CGPoint]()
                let bounds = selection.bounds
                quadrilateralPoints.append(CGPoint(x: bounds.minX, y: bounds.maxY))
                quadrilateralPoints.append(CGPoint(x: bounds.maxX, y: bounds.maxY))
                quadrilateralPoints.append(CGPoint(x: bounds.minX, y: bounds.minY))
                quadrilateralPoints.append(CGPoint(x: bounds.maxX, y: bounds.minY))
                
                // Create a highlight annotation
                let highlight = CPDFMarkupAnnotation(document: document, markupType: .highlight)
                highlight?.color = UIColor.yellow
                highlight?.quadrilateralPoints = quadrilateralPoints
                page4?.addAnnotation(highlight)
            }
        }
        
        // Create a note annotation
        let text = CPDFTextAnnotation(document: document)
        text?.contents = "test"
        text?.bounds = CGRect(x: 50, y: 200, width: 50, height: 50)
        text?.color = UIColor.yellow
        page4?.addAnnotation(text)
        
        // Create a link annotation
        let dest = CPDFDestination(document: document, pageIndex: 1)
        let link = CPDFLinkAnnotation(document: document)
        link?.bounds = CGRect(x: 50, y: 100, width: 50, height: 50)
        link?.setDestination(dest) // link.URL = “https://www.”
        page4?.addAnnotation(link)
        
        // Create a sound annotation
        // need import a recording file
        let filePath = Bundle.main.path(forResource: "Bird", ofType: "wav")
        let soundAnnotation = CPDFSoundAnnotation(document: document)
        if ((soundAnnotation?.setMediaPath(filePath)) == true) {
            soundAnnotation?.bounds = CGRect(x: 100, y: 200, width: 50, height: 50)
            page4?.addAnnotation(soundAnnotation)
        }
        
        //-----------------------------------------------------------------------------------------
        // Test of stamp annotation
        
        let page5 = document?.page(at: 4)
        let size5 = document?.pageSize(at: 4)
        let height5 = size5?.height ?? 0
        
        for i in 1...23 {
            let standard = CPDFStampAnnotation(document: document, type: i)
            standard?.bounds = CGRect(x: 50, y: height5 - CGFloat(i*30), width: 50, height: 30)
            page5?.addAnnotation(standard)
        }
        
        // Create a text stamp annotation
        let timename = NSTimeZone.system
        let outputFormatter = DateFormatter()
        outputFormatter.timeZone = timename
        // Get date
        var tDate: String?
        outputFormatter.dateFormat = "yyyy-MM-dd HH:mm:SS"
        tDate = outputFormatter.string(from: Date())
        let textStamp = CPDFStampAnnotation(document: document, text: "ComPDFKit", detailText: tDate, style: .red, shape: .arrowLeft)
        textStamp?.bounds = CGRect(x: 150, y: height5 - 50, width: 80, height: 50)
        page5?.addAnnotation(textStamp)
        
        // Create a Image stamp annotation
        let imageStamp = CPDFStampAnnotation(document: document, image: UIImage(named: "Logo"))
        imageStamp?.bounds = CGRect(x: 150, y: height5 - 120, width: 50, height: 50)
        page5?.addAnnotation(imageStamp)
        
        // Save the created annotation action in document
        document?.write(to: self.annotationURL)
        self.commandLineStr += "Done.\n"
        self.commandLineStr += "Done. Results saved in CreateAnnotationTest.pdf\n"
        
        // Refresh the document
        self.document = CPDFDocument(url: self.annotationURL)
    }
    
    // Print annotation list information
    func printAnnotationList(_ document: CPDFDocument?) {
        var annotations = [CPDFAnnotation]()
        for i in 0..<(document?.pageCount ?? 0) {
            // Loop through all annotation
            let page = document?.page(at: i)
            annotations.append(contentsOf: page?.annotations ?? [])
            
            for annotation in annotations {
                self.commandLineStr += "-------------------------------------\n"
                self.commandLineStr += "Page: \(i+1)\n"
                self.commandLineStr += "Annot Type:" + annotation.type + "\n"
                self.commandLineStr += "    Position: \(Int(annotation.bounds.origin.x)), \(Int(annotation.bounds.origin.y)), \(Int(annotation.bounds.size.width)), \(Int(annotation.bounds.size.height))\n\n"
            }
        }
    }
    
    // Dele the first annotation
    func deleteTestAnnot(_ oldDocument: CPDFDocument?) {
        // Get Sandbox path for saving the PDFFile
        let path = NSHomeDirectory() + "/Documents"
        let writeDirectoryPath = path + "/Annoation"
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath + "/DeleteAnnotationTest.pdf"
        
        // Save the document in the PDF file
        deleteAnnotationURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: deleteAnnotationURL)
        
        // Create a new document for test PDF file
        let document = CPDFDocument(url: deleteAnnotationURL)
        
        // Remove the first annotation from document
        let page = document?.page(at: 0)
        
        if let annotation = page?.annotations.first {
            page?.removeAnnotation(annotation)
        }
        
        // Save the remove the first annotation action in document
        document?.write(to: deleteAnnotationURL)
        self.commandLineStr += "Done.\n"
        self.commandLineStr += "Done. Results saved in DeleteAnnotationTest.pdf\n"
    }
    
    func openFile(with url: URL?) {
        if(url != nil) {
            let activityVC = UIActivityViewController(activityItems: [url!], applicationActivities: nil)
            activityVC.definesPresentationContext = true
            if UI_USER_INTERFACE_IDIOM() == .pad {
                activityVC.popoverPresentationController?.sourceView = self.openfileButton
                activityVC.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            
            present(activityVC, animated: true, completion: nil)
            
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
