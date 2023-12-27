//
//  CInteractiveFormsViewController.swift
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
// The sample code illustrates how to create and delete interactiveforms using API,
// also help you get interactiveforms list message.
//-----------------------------------------------------------------------------------------

class CInteractiveFormsViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""
    var exportFilePath = ""
    var interactiveFormsURL:URL?
    var deleteInteractiveFormsURL:URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("The sample code illustrates how to create and delete interactiveforms using API,also help you get interactiveforms list message.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        
        if isRun {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = self.openfileButton
                alertController.popoverPresentationController?.sourceRect = self.openfileButton.bounds
            }
            
            let createInteractiveFormsAction = UIAlertAction(title: NSLocalizedString("CreateInteractiveFormsTest.pdf", comment: ""), style: .default) { [weak self] action in
                // Open CreateInteractiveFormsTest.pdf
                if let url = self?.interactiveFormsURL {
                    self?.openFile(with: url)
                }
            }
            
            let deleteInteractiveFormsAction = UIAlertAction(title: NSLocalizedString("DeleteInteractiveFormsTest.pdf", comment: ""), style: .default) { [weak self] action in
                // Open DeleteInteractiveFormsTest.pdf
                if let url = self?.deleteInteractiveFormsURL {
                    self?.openFile(with: url)
                }
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(createInteractiveFormsAction)
            alertController.addAction(deleteInteractiveFormsAction)
            alertController.addAction(cancelAction)
            
            present(alertController, animated: false, completion: nil)
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
            
            present(alertController, animated: false, completion: nil)
        }

    }
    
    override func buttonItemClick_run(_ sender: Any) {
        if document != nil {
            self.isRun = true

            self.commandLineStr += "Running InteractiveForms sample...\n\n"
            createTestForms(oldDocument: document)
            printFormsMessage(document: document)
            deleteForm(oldDocument: document)
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
    func createTestForms(oldDocument: CPDFDocument?) {
        // Get the Sandbox path for saving the PDF file
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/InteractiveForms")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath + "/CreateInteractiveFormsTest.pdf"
        
        // Save the document to the test PDF file
        self.interactiveFormsURL = URL(fileURLWithPath: writeFilePath)

        oldDocument?.write(to: interactiveFormsURL)
        
        // Create a new document for the test PDF file
        if let document = CPDFDocument(url: interactiveFormsURL) {
            // Create a form using the API
            if let page = document.page(at: 0) {
                let pageSize = document.pageSize(at: 0)
                let height = pageSize.height
                
                // Your code to work with the new document and create interactive forms
                let textWidget1 = CPDFTextWidgetAnnotation(document: document)
                let bounds = self.view.convert(CGRect(x: 28, y: height - 30, width: 80, height: 25), to: self.view)
                textWidget1?.bounds = bounds
                textWidget1?.setFieldName("TextField1")
                textWidget1?.isMultiline = false
                textWidget1?.stringValue = "Basic Text Field"
                textWidget1?.fontColor = UIColor.black
                textWidget1?.font = UIFont.systemFont(ofSize: 15)
                page.addAnnotation(textWidget1)
                
                let textWidget2 = CPDFTextWidgetAnnotation(document: document)
                let boundsz = self.view.convert(CGRect(x: 28, y: height - 100, width: 80, height: 60), to: self.view)
                textWidget2?.bounds = boundsz
                textWidget2?.setFieldName("TextField2")
                textWidget2?.isMultiline = true
                textWidget2?.stringValue = "Basic Text Field\nBasic Text Field\nBasic Text Field"
                textWidget2?.fontColor = UIColor.black
                textWidget2?.font = UIFont.systemFont(ofSize: 15)
                page.addAnnotation(textWidget2)

                
                var items = [CPDFChoiceWidgetItem]()
                let item1 = CPDFChoiceWidgetItem()
                item1.value = "List Box No.1"
                item1.string = "List Box No.1"
                items.append(item1)

                let item2 = CPDFChoiceWidgetItem()
                item2.value = "List Box No.2"
                item2.string = "List Box No.2"
                items.append(item2)

                let item3 = CPDFChoiceWidgetItem()
                item3.value = "List Box No.3"
                item3.string = "List Box No.3"
                items.append(item3)

                let choiceWidget = CPDFChoiceWidgetAnnotation(document: document, listChoice: true)
                choiceWidget?.setFieldName("ListBox1")
                choiceWidget?.bounds = CGRect(x: 267, y: height - 100, width: 200, height: 100)
                choiceWidget?.items = items
                choiceWidget?.selectItemAtIndex = 2
                page.addAnnotation(choiceWidget)
                
                
                var itemsz = [CPDFChoiceWidgetItem]()
                let item1z = CPDFChoiceWidgetItem()
                item1z.value = "Combo Box No.1"
                item1z.string = "Combo Box No.1"
                itemsz.append(item1z)

                let item2z = CPDFChoiceWidgetItem()
                item2z.value = "Combo Box No.2"
                item2z.string = "Combo Box No.2"
                itemsz.append(item2z)

                let item3z = CPDFChoiceWidgetItem()
                item3z.value = "Combo Box No.3"
                item3z.string = "Combo Box No.3"
                itemsz.append(item3z)

                let choiceWidgetz = CPDFChoiceWidgetAnnotation(document: document, listChoice: false)
                choiceWidgetz?.setFieldName("ComboBox1")
                choiceWidgetz?.bounds = CGRect(x: 267, y: height - 100, width: 200, height: 100)
                choiceWidgetz?.items = itemsz
                choiceWidgetz?.selectItemAtIndex = 2
                page.addAnnotation(choiceWidgetz)

                let signatureWidget = CPDFSignatureWidgetAnnotation(document: document)
                signatureWidget?.bounds = CGRect(x: 28, y: height - 206, width: 80, height: 101)
                signatureWidget?.setFieldName("Signature1")
                page.addAnnotation(signatureWidget)
                
                let pushButton = CPDFButtonWidgetAnnotation(document: document, controlType: .pushButtonControl)
                pushButton?.bounds = CGRect(x: 267, y: height - 300, width: 130, height: 80)
                pushButton?.setFieldName("PushButton1")
                pushButton?.setCaption("PushButton")
                pushButton?.fontColor = UIColor.black
                pushButton?.font = UIFont.systemFont(ofSize: 15)

                let destination = CPDFDestination(document: document, pageIndex: 1)
                let goToAction = CPDFGoToAction(destination: destination)
                pushButton?.setAction(goToAction)

                page.addAnnotation(pushButton)

                //Insert CheckBox Widget
                let pushButtonz = CPDFButtonWidgetAnnotation(document: document, controlType: .pushButtonControl)
                pushButtonz?.bounds = CGRect(x: 367, y: height - 303, width: 150, height: 80)
                pushButtonz?.setFieldName("PushButton2")
                pushButtonz?.setCaption("PushButton")
                pushButtonz?.fontColor = UIColor.black
                pushButtonz?.font = UIFont.systemFont(ofSize: 15)

                let urlAction = CPDFURLAction(url: "https://www.compdf.com/")
                pushButtonz?.setAction(urlAction)

                page.addAnnotation(pushButtonz)

                //Insert CheckBox Widget
                let checkBox = CPDFButtonWidgetAnnotation(document: document, controlType: .checkBoxControl)
                checkBox?.bounds = CGRect(x: 67, y: height - 351, width: 100, height: 90)
                checkBox?.setFieldName("CheckBox1")
                checkBox?.borderColor = UIColor.black
                checkBox?.backgroundColor = UIColor.green
                checkBox?.borderWidth = 2.0
                checkBox?.setState(0)
                checkBox?.font = UIFont.systemFont(ofSize: 15)

                page.addAnnotation(checkBox)
                
                //Insert CheckBox Widget
                let checkBoxz = CPDFButtonWidgetAnnotation(document: document, controlType: .checkBoxControl)
                checkBoxz?.bounds = CGRect(x: 167, y: height - 351, width: 100, height: 90)
                checkBoxz?.setFieldName("CheckBox2")
                checkBoxz?.borderColor = UIColor.black
                checkBoxz?.backgroundColor = UIColor.green
                checkBoxz?.borderWidth = 2.0
                checkBoxz?.setState(0)
                checkBoxz?.font = UIFont.systemFont(ofSize: 15)
                page.addAnnotation(checkBoxz)
                
                let radioButton = CPDFButtonWidgetAnnotation(document: document, controlType: .radioButtonControl)
                radioButton?.bounds = CGRect(x: 167, y: height - 451, width: 100, height: 90)
                radioButton?.setFieldName("RadioButton1")
                radioButton?.borderColor = UIColor.black
                radioButton?.backgroundColor = UIColor.green
                radioButton?.borderWidth = 2.0
                radioButton?.setState(0)
                radioButton?.font = UIFont.systemFont(ofSize: 15)
                page.addAnnotation(radioButton)
                
                let radioButtonz = CPDFButtonWidgetAnnotation(document: document, controlType: .radioButtonControl)
                radioButtonz?.bounds = CGRect(x: 267, y: height - 451, width: 100, height: 90)
                radioButtonz?.setFieldName("RadioButton2")
                radioButtonz?.borderColor = UIColor.black
                radioButtonz?.backgroundColor = UIColor.green
                radioButtonz?.borderWidth = 2.0
                radioButtonz?.setState(0)
                radioButtonz?.font = UIFont.systemFont(ofSize: 15)
                page.addAnnotation(radioButtonz)
                
                let radioButtonh = CPDFButtonWidgetAnnotation(document: document, controlType: .radioButtonControl)
                radioButtonh?.bounds = CGRect(x: 367, y: height - 451, width: 100, height: 90)
                radioButtonh?.setFieldName("RadioButton3")
                radioButtonh?.borderColor = UIColor.black
                radioButtonh?.backgroundColor = UIColor.green
                radioButtonh?.borderWidth = 2.0
                radioButtonh?.setState(0)
                radioButtonh?.font = UIFont.systemFont(ofSize: 15)
                page.addAnnotation(radioButtonh)
                
                document.write(to: interactiveFormsURL)

                self.document = CPDFDocument(url: self.interactiveFormsURL)

                self.commandLineStr += "Done.\n"
                self.commandLineStr += "Done. Results saved in CreateInteractiveFormsTest.pdf\n"
            }
        }
    }
    
    func printFormsMessage(document: CPDFDocument?) {
        let page = document?.page(at: 0)

        if let annotations = page?.annotations {
            for annotationz in annotations {
                if let annotation = annotationz as? CPDFWidgetAnnotation {

                    commandLineStr += "Field name :" + annotation.fieldName() + "\n"
                    
                    if let textWidgetAnnotation = annotation as? CPDFTextWidgetAnnotation {
                        commandLineStr += "Field partial name : \(textWidgetAnnotation.stringValue ?? "")\n"
                    } else if let buttonWidgetAnnotation = annotation as? CPDFButtonWidgetAnnotation {
                        switch buttonWidgetAnnotation.controlType() {
                        case .radioButtonControl:
                            commandLineStr += "Field isChecked : \(buttonWidgetAnnotation.state())\n"
                        case .pushButtonControl:
                            commandLineStr += "Field PushButton Title : \(buttonWidgetAnnotation.caption() ?? "")\n"
                            
                            if let action = buttonWidgetAnnotation.action() {
                                if let urlAction = action as? CPDFURLAction {
                                    commandLineStr += "Field PushButton Action : \(urlAction.url() ?? "")\n"
                                } else if let goToAction = action as? CPDFGoToAction {
                                    commandLineStr += "Field PushButton Action : Jump to page \(goToAction.destination().pageIndex) of the document\n"
                                }
                            }
                        case .checkBoxControl:
                            commandLineStr += "Field isChecked : \(buttonWidgetAnnotation.state())\n"
                        case .unknownControl: break
                            
                            
                        @unknown default: break
                            
                        }
                    } else if let choiceWidgetAnnotation = annotation as? CPDFChoiceWidgetAnnotation {
                        commandLineStr += "Field Select Item : \(choiceWidgetAnnotation.selectItemAtIndex)\n"
                    }
                    
                    commandLineStr += "    Position: \(Int(annotation.bounds.origin.x)), \(Int(annotation.bounds.origin.y)), \(Int(annotation.bounds.size.width)), \(Int(annotation.bounds.size.height))\n"
                    commandLineStr += "Widget type : \(annotation.type ?? "")\n"
                    commandLineStr += "-------------------------------------\n"
                }
            }
        }

    }

    func deleteForm(oldDocument: CPDFDocument?) {
        // Get the Sandbox path for saving the PDF file
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/InteractiveForms")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        }
        
        let writeFilePath = writeDirectoryPath + "/DeleteInteractiveFormsTest.pdf"
        
        // Save the document in the test PDF file
        self.deleteInteractiveFormsURL = URL(fileURLWithPath: writeFilePath)
        oldDocument?.write(to: self.deleteInteractiveFormsURL)
        
        // Create a new document for the test PDF file
        if let document = CPDFDocument(url: self.deleteInteractiveFormsURL) {
            // Remove the first form from the document
            if let page = document.page(at: 0) {
                if let annotation = page.annotations.first {
                    page.removeAnnotation(annotation)
                }
            }
            
            // Save the removed form action in the document
            document.write(to: self.deleteInteractiveFormsURL)
            
            self.commandLineStr += "Done.\n"
            self.commandLineStr += "Done. Results saved in DeleteInteractiveFormsTest.pdf\n"
        }
    }
    
    func openFile(with url: URL) {
        let activityVC = UIActivityViewController(activityItems: [url], applicationActivities: nil)
        activityVC.definesPresentationContext = true
        
        if UIDevice.current.userInterfaceIdiom == .pad {
            activityVC.popoverPresentationController?.sourceView = self.openfileButton
            activityVC.popoverPresentationController?.sourceRect = self.openfileButton.bounds
        }
        
        self.present(activityVC, animated: true, completion: nil)
        
        activityVC.completionWithItemsHandler = { activityType, completed, returnedItems, activityError in
            if completed {
                print("Success!")
            } else {
                print("Failed Or Canceled!")
            }
        }
    }




    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
