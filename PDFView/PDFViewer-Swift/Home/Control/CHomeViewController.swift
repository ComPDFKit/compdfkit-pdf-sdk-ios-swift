//
//  CHomeViewController.swift
//  ComPDFKit_Tools
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

import UIKit
import ComPDFKit_Tools
import ComPDFKit

class CHomeViewController: UIViewController,UITableViewDelegate,UITableViewDataSource, UIDocumentPickerDelegate, CPDFViewBaseControllerDelete,CPDFCompressViewControllerDelegate {
    
    var tabview:UITableView?
    var jsonDataParse:CPDFJSONDataParse?
    var compressDocument: CPDFDocument?
    private var okAction: UIAlertAction?
    var textField: UITextField?
    
    private lazy var featureArrays: [Dictionary<String, Any>] = {
        let viewFeature: [String: Any] = ["title": NSLocalizedString("Viewer", comment: ""),
                                          "image": "CHomeImageFeatureView",
                                          "subtitle": NSLocalizedString("High-quality rendering speed and rich reading tools support a smooth reading experience.", comment: ""),
                                          "type":CHomeFeature.viewer.rawValue]
        
        let annotationsFeature: [String: Any] = ["title": NSLocalizedString("Annotations", comment: ""),
                                                 "image": "CHomeImageFeatureaAnnotations",
                                                 "subtitle": NSLocalizedString("Add, edit, delete, export, import, and flatten various annotations and markups on PDFs.", comment: ""),
                                                 "type":CHomeFeature.annotation.rawValue]
        
        let formsFeature: [String: Any] = ["title": NSLocalizedString("Forms", comment: ""),
                                           "image": "CHomeImageFeatureForms",
                                           "subtitle": NSLocalizedString("Create, edit, and fill in PDF forms, with support for importing, exporting, and flattening forms.", comment: ""),
                                           "type":CHomeFeature.form.rawValue]
        
        let signaturesFeature: [String: Any] = ["title": NSLocalizedString("Signatures", comment: ""),
                                                "image": "CHomeImageFeatureSignatures",
                                                "subtitle": NSLocalizedString("Easily sign PDFs with drawn, images, typed signatures, or a digital ID.", comment: ""),
                                                "type":CHomeFeature.signatures.rawValue]
        
        let documentEditorFeature: [String: Any] = ["title": NSLocalizedString("Document Editor", comment: ""),
                                                    "image": "CHomeImageFeatureDocumentEditor",
                                                    "subtitle": NSLocalizedString("Add, insert, replace, extract, reverse, move, copy, paste, rotate, delete, crop, and zoom PDF pages.", comment: ""),
                                                    "type":CHomeFeature.documentEdit.rawValue]
        let contentEditorFeature: [String: Any] = ["title": NSLocalizedString("Content Editor", comment: ""),
                                                   "image": "CHomeImageFeatureContentEditor",
                                                   "subtitle": NSLocalizedString("Edit the PDF text and images like edit in Word. You can freely adjust the size, position, style, font, etc.", comment: ""),
                                                   "type":CHomeFeature.contentEdit.rawValue]
        let securityFeature: [String: Any] = ["title": NSLocalizedString("Security", comment: ""),
                                              "image": "CHomeImageFeatureSecurity",
                                              "subtitle": NSLocalizedString("Encrypt/decrypt PDFs, edit file permissions, headers and footers, backgrounds, Bates numbers, etc.", comment: ""),
                                              "type":CHomeFeature.security.rawValue]
        let redactionFeature: [String: Any] = ["title": NSLocalizedString("Redaction", comment: ""),
                                               "image": "CHomeImageFeatureRedaction",
                                               "subtitle": NSLocalizedString("Use redaction to remove sensitive images, text, and vector graphics.", comment: ""),
                                               "type":CHomeFeature.redaction.rawValue]
        let watermarkFeature: [String: Any] = ["title": NSLocalizedString("Watermark", comment: ""),
                                               "image": "CHomeImageFeatureWatermark",
                                               "subtitle": NSLocalizedString("Create, insert, and remove text or image watermarks to brand the files.", comment: ""),
                                               "type":CHomeFeature.watermark.rawValue]
        let compareFeature: [String: Any] = ["title": NSLocalizedString("Compare Documents", comment: ""),
                                             "image": "CHomeImageFeatureCompare",
                                             "subtitle": NSLocalizedString("Allow to compare PDF files and design drawings with content comparison and overlay comparison.", comment: ""),
                                             "type":CHomeFeature.compareDocument.rawValue]
        let conversionFeature: [String: Any] = ["title": NSLocalizedString("Conversion", comment: ""),
                                                "image": "CHomeImageFeatureConvert",
                                                "subtitle": NSLocalizedString("Support the mutual conversion between PDF files and Office, image types, text types, HTML, PDF/A, etc.", comment: ""),
                                                "type":CHomeFeature.conversion.rawValue]
        let compressFeature: [String: Any] = ["title": NSLocalizedString("Compress", comment: ""),
                                              "image": "CHomeImageFeatureCompress",
                                              "subtitle": NSLocalizedString("Optimize and reduce PDF document size with no or minimum visual quality loss.", comment: ""),
                                              "type":CHomeFeature.compress.rawValue]
        let measureFeature: [String: Any] = ["title": NSLocalizedString("Measurement", comment: ""),
                                             "image": "CHomeImageFeatureMeasure",
                                             "subtitle": NSLocalizedString("Measure the distance, perimeter, area, angle, diameter, radius, and volume measurement annotations.", comment: ""),
                                             "type":CHomeFeature.measurement.rawValue]
        
        return [viewFeature,
                annotationsFeature,
                formsFeature,
                signaturesFeature,
                documentEditorFeature,
                contentEditorFeature,
                compressFeature,
                securityFeature,
                redactionFeature,
                watermarkFeature,
                compareFeature,
                conversionFeature,
                measureFeature]
    }()
    
    private lazy var fileArrays: [String] = {
        return ["ComPDFKit_Sample_File_iOS"]
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.title = NSLocalizedString("ComPDFKit Demo for iOS", comment: "")
        
        let setBarItem = UIBarButtonItem(image: UIImage(named: "CHomeImageSetting", in: Bundle(for: self.classForCoder), compatibleWith: nil), style: .done, target: self, action: #selector(buttonItemClick_Setting(_:)))
        self.navigationItem.rightBarButtonItems = [setBarItem]
        
        tabview = UITableView.init(frame: self.view.bounds, style: .plain)
        tabview?.delegate = self
        tabview?.dataSource = self
        tabview?.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        tabview?.separatorStyle = .none
        if(tabview != nil) {
            view.addSubview(tabview!)
        }
        
    }
    
    // MARK: - Action
    @objc func buttonItemClick_Setting(_ button: UIBarButtonItem) {
        let settingVC = CHomeSettingViewController(nibName: nil, bundle: nil)
        let navController = CNavigationController(rootViewController: settingVC)
        self.present(navController, animated: true)
    }
    
    @objc func buttonItemClicked_showOwerPassword(_ button: UIButton) {
        if button.isSelected == true {
            button.isSelected = false
            textField?.isSecureTextEntry = true
        } else {
            button.isSelected = true
            textField?.isSecureTextEntry = false
            
        }
    }
    
    // MARK: - UITableViewDataSource
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if(section == 0) {
            return self.featureArrays.count
        } else {
            return self.fileArrays.count
        }
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 2
    }
    
    func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 38.0
    }
    
    func tableView(_ tableView: UITableView, viewForHeaderInSection section: Int) -> UIView? {
        let haderView = UITableViewHeaderFooterView(frame: CGRect(x: 0, y: 0, width: self.view.frame.width, height: 28.0))
        haderView.autoresizingMask = .flexibleWidth
        let titlelabel = UILabel(frame: CGRect(x: 10, y: 4, width: haderView.frame.width-20, height: 20))
        titlelabel.font = UIFont.boldSystemFont(ofSize: 13)
        var title: String = ""
        switch section {
        case 0:
            title = NSLocalizedString("Features", comment: "")
        case 1:
            title = NSLocalizedString("Click to Open & Process", comment: "")
        default:
            title = ""
        }
        titlelabel.text = title
        haderView.addSubview(titlelabel)
        return haderView
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        if(indexPath.section == 0) {
            return 70.0
        } else {
            return 58
        }
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        if(indexPath.section == 0) {
            var cell = tableView.dequeueReusableCell(withIdentifier: "featuresCell") as? CHomeFeaturesTableViewCell
            if(cell == nil) {
                cell = CHomeFeaturesTableViewCell.init(style: .default, reuseIdentifier: "featuresCell")
            }
            let featureDic = self.featureArrays[indexPath.row]
            cell?.featureTitle?.text = featureDic["title"] as? String
            cell?.featureSubTitle?.text = featureDic["subtitle"] as? String
            cell?.featureImage?.image = UIImage(named: featureDic["image"] as? String ?? "", in: Bundle(for: self.classForCoder), compatibleWith: nil)
            cell?.accessoryType = .disclosureIndicator
            return cell!
        } else {
            var cell = tableView.dequeueReusableCell(withIdentifier: "cell") as? CHomeFileTableViewCell
            if(cell == nil) {
                cell = CHomeFileTableViewCell.init(style: .default, reuseIdentifier: "featuresCell")
            }
            
            let filePath = Bundle.main.path(forResource: self.fileArrays[indexPath.row], ofType: "pdf")
            
            let nameTitle = (filePath as NSString?)?.lastPathComponent ?? ""
            cell?.nameTitle?.text = NSLocalizedString(nameTitle, comment: "")
            
            cell?.thumImage?.image = UIImage(named: "CHomeImagePDFThum", in: Bundle(for: self.classForCoder), compatibleWith: nil)
            let documentFolder = SAMPLESFOLDER
            
            let documentURL = URL(fileURLWithPath: documentFolder).appendingPathComponent((filePath as NSString?)?.lastPathComponent ?? "")
            
            if let attrib = try? FileManager.default.attributesOfItem(atPath: documentURL.path),
               let fileSize = attrib[FileAttributeKey.size] as? Float,
               let fileModDate = attrib[FileAttributeKey.modificationDate] as? Date {
                
                let dateFormatter = DateFormatter()
                dateFormatter.dateFormat = "yyyy/MM/dd HH:mm"
                let formattedDate = dateFormatter.string(from: fileModDate)
                
                var size = fileSize / 1024
                var unit: String
                if size >= 1024 {
                    if size < 1048576 {
                        size /= 1024.0
                        unit = "M"
                    } else {
                        size /= 1048576.0
                        unit = "G"
                    }
                } else {
                    unit = "K"
                }
                
                let formattedSize = String(format: "%0.1f%@", size, unit)
                
                cell?.subNameTitle?.text = formattedDate + "  " + formattedSize
            }
            cell?.accessoryType = .none
            
            return cell!
            
        }
    }
    
    // MARK: - UITableViewDelegate
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: false)
        if(indexPath.section == 1) {
            let filePath = Bundle.main.path(forResource: self.fileArrays[indexPath.row], ofType: "pdf")
            let documentFolder = SAMPLESFOLDER
            
            let documentURL = URL(fileURLWithPath: documentFolder).appendingPathComponent((filePath as NSString?)?.lastPathComponent ?? "")
            
            let configuration = CPDFConfiguration()
            
            let pdfViewController = CPDFViewController(filePath: documentURL.path, password: nil, configuration: configuration)
            let navController = CNavigationController(rootViewController: pdfViewController)
            pdfViewController.delegate = self
            navController.modalPresentationStyle = .fullScreen
            self.present(navController, animated: true)
        } else {
            switch indexPath.row {
            case 0...5:
                let featureDic = self.featureArrays[indexPath.row]
                let featureType = CHomeFeature(rawValue: featureDic["type"] as? Int ?? 0)
                let featureVC = CHomeFileListController.init(feature: featureType ?? .viewer)
                let navController = CNavigationController(rootViewController: featureVC)
                navController.modalPresentationStyle = .fullScreen
                self.present(navController, animated: true)
            case 6:
                openCompressPDF()
            case 7:
                let featureDic = self.featureArrays[indexPath.row]
                let featureType = CHomeFeature(rawValue: featureDic["type"] as? Int ?? 0)
                let featureVC = CHomeFileListController.init(feature: featureType ?? .viewer)
                let navController = CNavigationController(rootViewController: featureVC)
                navController.modalPresentationStyle = .fullScreen
                self.present(navController, animated: true)
            case 8:
                if let url = URL(string: "https://www.compdf.com/pdf-sdk/security") {
                    UIApplication.shared.open(url)
                }
            case 9:
                let featureDic = self.featureArrays[indexPath.row]
                let featureType = CHomeFeature(rawValue: featureDic["type"] as? Int ?? 0)
                let featureVC = CHomeFileListController.init(feature: featureType ?? .viewer)
                let navController = CNavigationController(rootViewController: featureVC)
                navController.modalPresentationStyle = .fullScreen
                self.present(navController, animated: true)
            case 10:
                if let url = URL(string: "https://www.compdf.com/pdf-sdk/document-comparison") {
                    UIApplication.shared.open(url)
                }
            case 11:
                if let url = URL(string: "https://www.compdf.com/conversion") {
                    UIApplication.shared.open(url)
                }
            case 12:
                if let url = URL(string: NSLocalizedString("https://www.compdf.com/contact-sales", comment: "")) {
                    UIApplication.shared.open(url)
                }
            default:
                if let url = URL(string: "https://www.compdf.com/") {
                    UIApplication.shared.open(url)
                }
            }
            
        }
    }
    
    // MARK: - Private Methods
    
    private  func openCompressPDF() {
        let documentTypes = ["com.adobe.pdf"]
        let documentPickerViewController = UIDocumentPickerViewController(documentTypes: documentTypes, in: .open)
        documentPickerViewController.delegate = self
        UIApplication.presentedViewController()?.present(documentPickerViewController, animated: true, completion: nil)
    }
    
    @objc func textField_change(_ sender: UITextField) {
        if let text = sender.text, !text.isEmpty {
               okAction?.isEnabled = true
               okAction?.setValue(UIColor.systemBlue, forKey: "titleTextColor")
           } else {
               okAction?.isEnabled = false
               okAction?.setValue(UIColor.gray, forKey: "titleTextColor")
           }
    }
    
    func enterPermissionPassword(pdfDocument:CPDFDocument) {
        let alert = UIAlertController(title: NSLocalizedString("Enter Owner's Password to Change the Security", comment: ""), message: "", preferredStyle: .alert)
        alert.addTextField { (textField) in
            
        }
        let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
        
        let addAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default) { (action) in
            if let text = alert.textFields?.first?.text, !text.isEmpty {
                let result = pdfDocument.unlock(withPassword: text)
                if result == true {
                    if pdfDocument.permissionsStatus == .owner {
                        self.compressDocument = pdfDocument
                        let viewController = CPDFCompressViewController(compressDocument: pdfDocument)
                        viewController.password = text;
                        viewController.delegate = self
                        self.navigationController?.pushViewController(viewController, animated: true)
                    } else {
                        self.enterPermissionPassword(pdfDocument: pdfDocument)
                    }
                } else {
                    self.enterPermissionPassword(pdfDocument: pdfDocument)
                }
            } else {
                self.enterPermissionPassword(pdfDocument: pdfDocument)
            }
        }
        
        
        alert.addAction(cancelAction)
        alert.addAction(addAction)
        present(alert, animated: true, completion: nil)
    }
    
    // MARK: - UIDocumentPickerDelegate
    
    func documentPicker(_ controller: UIDocumentPickerViewController, didPickDocumentsAt urls: [URL]) {
        let fileUrlAuthozied = urls.first?.startAccessingSecurityScopedResource() ?? false
        if fileUrlAuthozied {
            let fileCoordinator = NSFileCoordinator()
            var error: NSError?
            fileCoordinator.coordinate(readingItemAt: urls.first!, options: [], error: &error) { newURL in
                let documentFolder = NSHomeDirectory() + "/Documents/Files"
                if !FileManager.default.fileExists(atPath: documentFolder) {
                    try? FileManager.default.createDirectory(atPath: documentFolder, withIntermediateDirectories: true, attributes: nil)
                }
                let documentPath = documentFolder+"/"+newURL.lastPathComponent
                if !FileManager.default.fileExists(atPath: documentPath) {
                    try? FileManager.default.copyItem(atPath: newURL.path, toPath: documentPath)
                }
                
                let url = URL(fileURLWithPath: documentPath)
                
                guard let document = CPDFDocument(url: url) else {
                    print("Document is NULL")
                    return
                }
                
    
                if let error = document.error, error._code != CPDFDocumentPasswordError {
                    let okAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default) { _ in }
                    let alert = UIAlertController(title: "", message: NSLocalizedString("Sorry PDF Reader Can't open this pdf file!", comment: ""), preferredStyle: .alert)
                    alert.addAction(okAction)
                    let tRootViewControl = self
                    tRootViewControl.present(alert, animated: true, completion: nil)
                } else {
                    if document.isLocked {
                        
                        
                        let alertController = UIAlertController(title: NSLocalizedString("Password", comment: ""), message: "", preferredStyle: .alert)
                        
                        // Add the text field to the alert controller
                        alertController.addTextField { [self] (textField) in
                            textField.placeholder = NSLocalizedString("Please enter the password", comment: "")
                            let owerPasswordBtton = UIButton(type: .custom)
                            owerPasswordBtton.addTarget(self, action: #selector(self.buttonItemClicked_showOwerPassword(_:)), for: .touchUpInside)
                            owerPasswordBtton.setImage(UIImage(named: "CSecureImageInvisible", in: Bundle(for: self.classForCoder), compatibleWith: nil), for: .normal)
                            owerPasswordBtton.setImage(UIImage(named: "CSecureImageVisible", in: Bundle(for: self.classForCoder), compatibleWith: nil), for: .selected)
                            owerPasswordBtton.frame = CGRect(x:0, y:0, width:25, height:25)
                            
                            textField.addTarget(self, action: #selector(textField_change(_:)), for: .editingChanged)
                            textField.isSecureTextEntry = true
                            textField.returnKeyType = .done
                            textField.rightViewMode = .always
                            textField.rightView = owerPasswordBtton
                            
                            self.textField = textField
                        }
                        
                        // Add the Cancel action
                        let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
                        alertController.addAction(cancelAction)
                        
                        // Add the OK action
                        okAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default) { (_) in
                            if let textField = alertController.textFields?.first, let text = textField.text {
                                // Do something with the text input
                                if document.unlock(withPassword: text) {
                                    if document.permissionsStatus == .owner {
                                        self.compressDocument = document
                                        let viewController = CPDFCompressViewController(compressDocument: document)
                                        viewController.password = text
                                        viewController.delegate = self
                                        self.navigationController?.pushViewController(viewController, animated: true)
                                    } else {
                                        self.enterPermissionPassword(pdfDocument: document)
                                    }
                                } else {
                                    let okAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default) { _ in }
                                    let alert = UIAlertController(title: "", message: NSLocalizedString("Incorrect password, please try again.", comment: ""), preferredStyle: .alert)
                                    alert.addAction(okAction)
                                    self.present(alert, animated: true, completion: nil)
                                }
                            }
                        }
                        okAction?.isEnabled = false
                        okAction?.setValue(UIColor.gray, forKey: "titleTextColor")
                        alertController.addAction(okAction!)
                        
                        // Present the alert controller
                        present(alertController, animated: true, completion: nil)
                    } else {
                        self.compressDocument = document
                        let viewController = CPDFCompressViewController(compressDocument: document)
                        viewController.delegate = self
                        self.navigationController?.pushViewController(viewController, animated: true)
                    }
                }
            }
            urls.first?.stopAccessingSecurityScopedResource()
        }
    }
    
    // MARK: - CPDFViewBaseControllerDelete
    func PDFViewBaseControllerDissmiss(_ baseControllerDelete: CPDFViewBaseController) {
        baseControllerDelete.dismiss(animated: true)
    }
    
    // MARK: - CPDFCompressViewControllerDelegate

    func compressViewController(_ viewController: CPDFCompressViewController, URL url: URL, Password password: String) {
        let configuration = CPDFConfiguration()
        
        let pdfViewController = CPDFViewController(filePath: url.path, password: password, configuration: configuration)
        let navController = CNavigationController(rootViewController: pdfViewController)
        pdfViewController.delegate = self
        navController.modalPresentationStyle = .fullScreen
        self.present(navController, animated: true)
        
        pdfViewController.isComPressing = true
        pdfViewController.reloadCompressTopView()
    }
    
}
