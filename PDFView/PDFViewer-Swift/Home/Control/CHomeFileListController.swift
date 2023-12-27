//
//  CHomeFileListController.swift
//  ComPDFKit_Tools
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
import ComPDFKit_Tools

enum CHomeFeature: Int {
    case viewer = 0
    case annotation
    case form
    case signatures
    case documentEdit
    case contentEdit
    case security
    case watermark
    case redaction
    case compareDocument
    case conversion
    case compress
    case measurement
}

class CHomeFileListController: UIViewController, UITableViewDelegate, UITableViewDataSource, UIDocumentPickerDelegate, CPDFViewBaseControllerDelete, CPDFAddWatermarkViewControllerDelegate, CDocumentPasswordViewControllerDelegate,CHomeInsertPageViewControllerDelegate {
    
    var feature:CHomeFeature = .viewer
    var tableView:UITableView?
    
    var fileArray: [URL] = []
    
    var updateFolderTimer: Timer?
    
    var path: String?
    
    var addBtn: UIButton?
    
    var textField: UITextField?
    
    var documentPasswordVC: CDocumentPasswordViewController?
    
    var pdfDocumentPasswordVC: CDocumentPasswordViewController?
    
    var isAddWatermark: Bool = true
    
    init(feature: CHomeFeature) {
        super.init(nibName: nil, bundle: nil)
        self.feature = feature
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let setBarItem = UIBarButtonItem(image: UIImage(named: "CHomeImageSetting", in: Bundle(for: self.classForCoder), compatibleWith: nil), style: .done, target: self, action: #selector(buttonItemClick_Setting(_:)))
        self.navigationItem.rightBarButtonItems = [setBarItem]
        
        let backItem = UIBarButtonItem(image: UIImage(named: "CPDFViewImageBack", in: Bundle(for: self.classForCoder), compatibleWith: nil), style: .plain, target: self, action: #selector(buttonItemClicked_back(_:)))
        self.navigationItem.leftBarButtonItems = [backItem]
        
        initPath()
        
        title = (path as NSString?)?.lastPathComponent
        
        tableView = UITableView(frame: view.bounds, style: .plain)
        tableView?.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        tableView?.delegate = self
        tableView?.dataSource = self
        if(tableView != nil) {
            view.addSubview(tableView!)
        }
        
        addBtn = UIButton(type: .custom)
        addBtn?.frame = CGRect(x: Int(self.view.frame.width) - 70, y: Int(self.view.frame.height) - 170, width: 50, height: 50)
        addBtn?.layer.cornerRadius = 25.0
        addBtn?.autoresizingMask = [.flexibleLeftMargin,.flexibleTopMargin]
        addBtn?.setImage(UIImage(named: "CHomeImageAddFile", in: Bundle(for: self.classForCoder), compatibleWith: nil), for: .normal)
        addBtn?.addTarget(self, action: #selector(buttonItemClick_Add(_:)), for: .touchUpInside)
        addBtn?.backgroundColor = UIColor.init(red: 20.0/255.0, green: 96.0/255.0, blue: 243/255.0, alpha: 1.0)
        if(addBtn != nil) {
            self.view.addSubview(addBtn!)
        }
        
        self.title = NSLocalizedString("ComPDFKit Demo for iOS", comment: "")
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        registTimer()
        reloadFileManagerData()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        unregistTimer()
    }
    
    // MARK: - Private Methods
    
    func initPath() {
        switch feature {
        case .viewer:
            path = VIEWERSFOLDER
        case .annotation:
            path = ANNOTATIONSFOLDER
        case .form:
            path = FORMSFOLDER
        case .signatures:
            path = SIGNATURESFOLDER
        case .documentEdit:
            path = DOCUMENTEDITORFOLDER
        case .contentEdit:
            path = CONTENTEDITORFOLDER
        case .security:
            path = SECURITYFOLDER
        case .watermark:
            path = WATERMARKFOLDER
        default:
            break
        }
        
    }
    
    func shareAction(url: URL?) {
        if (url != nil) {
            let activityVC = UIActivityViewController(activityItems: [url!], applicationActivities: nil)
            activityVC.definesPresentationContext = true
            if UI_USER_INTERFACE_IDIOM() == .pad {
                activityVC.popoverPresentationController?.sourceView = self.navigationController?.navigationBar ?? self.view
                activityVC.popoverPresentationController?.sourceRect = CGRect(x:self.navigationController?.navigationBar.width ?? 0, y:0, width:0, height:0)
            }
            self.present(activityVC, animated: true)
            activityVC.completionWithItemsHandler = { (activityType, completed, returnedItems, activityError) in
                if completed {
                    print("Success!")
                } else {
                    print("Failed Or Canceled!")
                }
            }
        }
    }
    
    func deleteWatermarkAction(_ document: CPDFDocument?) {
        if (!(FileManager.default.fileExists(atPath: TEMPOARTFOLDER))) {
            try? FileManager.default.createDirectory(atPath: TEMPOARTFOLDER, withIntermediateDirectories: true, attributes: nil)
        }
        
        guard let lastPathComponent = document?.documentURL.deletingPathExtension().lastPathComponent else { return  }
        
        let secPath = TEMPOARTFOLDER + "/" + lastPathComponent + "_Watermark_Removed.pdf"
        do {
            try FileManager.default.removeItem(atPath: secPath)
        } catch {
            // Handle the error, e.g., print an error message or perform other actions
        }
        
        let url = NSURL(fileURLWithPath: secPath) as URL
        
        document?.write(to: url)
        
        let newDocument = CPDFDocument(url: url)
        let watermarks = newDocument?.watermarks() ?? []
       
        for watermark in watermarks {
            newDocument?.removeWatermark(watermark)
        }
        
        newDocument?.write(to: url)
        
        shareAction(url: url)
    }
    
    func settingWaterMark(URL url: URL) {
        let document = CPDFDocument(url: url)
    
        let addWaterMarkAction = UIAlertAction(title: NSLocalizedString("Add Watermarks", comment: ""), style: .default) { _ in
            if document != nil && document?.isLocked == true {
                self.isAddWatermark = true
                self.documentPasswordVC = CDocumentPasswordViewController(document: document!)
                self.documentPasswordVC?.delegate = self
                self.documentPasswordVC?.modalPresentationStyle = .fullScreen
                self.present(self.documentPasswordVC!, animated: true, completion: nil)
            } else {
                let addWaterMarkVC = CPDFAddWatermarkViewController.init(fileURL: url, document: document)
                addWaterMarkVC.delegate = self
                self.navigationController?.pushViewController(addWaterMarkVC, animated: false)
            }
        }
        
        let deleteWaterMarkAction = UIAlertAction(title: NSLocalizedString("Remove Watermarks", comment: ""), style: .default) {_ in
            if document != nil && document?.isLocked == true {
                self.isAddWatermark = false
                self.documentPasswordVC = CDocumentPasswordViewController(document: document!)
                self.documentPasswordVC?.delegate = self
                self.documentPasswordVC?.modalPresentationStyle = .fullScreen
                self.present(self.documentPasswordVC!, animated: true, completion: nil)
            } else {
                self.deleteWatermarkAction(document)
            }
        }
        
        let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style:.cancel)
        
        let alertController = UIAlertController(title: nil, message: nil, preferredStyle: .actionSheet)
        alertController.addAction(addWaterMarkAction)
        alertController.addAction(deleteWaterMarkAction)
        alertController.addAction(cancelAction)
        
        let cell = tableView?.cellForRow(at: IndexPath(row: 0, section: 0))
        
        if UIDevice.current.userInterfaceIdiom == .pad {
            alertController.popoverPresentationController?.sourceView = cell
            alertController.popoverPresentationController?.sourceRect = cell?.bounds ?? .zero
        }
        
        self.present(alertController, animated: true)
            
    }
    
    func popAddWatermarkWarning(_ isSuccess: Bool) {
        if isSuccess {
            let cancelAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style:.cancel)
            
            let alertController = UIAlertController(title: "Add Watermarks Successfully!", message: nil, preferredStyle: .alert)
            alertController.addAction(cancelAction)
            self.present(alertController, animated: true)
        } else {
            let cancelAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style:.cancel)
            
            let alertController = UIAlertController(title: "Failed to Add the Watermarks.", message: nil, preferredStyle: .alert)
            alertController.addAction(cancelAction)
            self.present(alertController, animated: true)
        }
    }
    
    func popDeleteWatermarkWarning(_ isSuccess: Bool) {
        if isSuccess {
            let cancelAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style:.cancel)
            
            let alertController = UIAlertController(title: "Watermarks Removed Successfully!", message: nil, preferredStyle: .alert)
            alertController.addAction(cancelAction)
            self.present(alertController, animated: true)
        } else {
            let cancelAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style:.cancel)
            
            let alertController = UIAlertController(title: "Failed to Remove the Watermarks.", message: nil, preferredStyle: .alert)
            alertController.addAction(cancelAction)
            self.present(alertController, animated: true)
        }
    }
    
    func openSecurePDF(filePath:String) {
        let pdfDocument = CPDFDocument(url: NSURL.fileURL(withPath: filePath))
        // have open PassWord And have open+ower
        if pdfDocument != nil && pdfDocument?.isLocked == true {
            let documentPasswordVC = CDocumentPasswordViewController(document: pdfDocument!)
            documentPasswordVC.delegate = self
            documentPasswordVC.modalPresentationStyle = .fullScreen
            self.present(documentPasswordVC, animated: true, completion: nil)
        } else {
            if pdfDocument?.permissionsStatus == .user {
                enterPermissionPassword(pdfDocument: pdfDocument!)
            } else {
                enterSecurePDF(filePath: filePath, password: nil)
            }
        }
    }
    
    func enterSecurePDF(filePath:String,password:String?) {
        let secureVC = CPDFSecureViewController(filePath: filePath, password: password)
        self.navigationController?.pushViewController(secureVC, animated:true)
    }
    
    func enterPermissionPassword(pdfDocument:CPDFDocument) {
        let alert = UIAlertController(title: NSLocalizedString("Enter Owner's Password to Change the Security", comment: ""), message: "", preferredStyle: .alert)
        alert.addTextField { (textField) in
            let owerPasswordBtton = UIButton(type: .custom)
            owerPasswordBtton.addTarget(self, action: #selector(self.buttonItemClicked_showOwerPassword(_:)), for: .touchUpInside)
            owerPasswordBtton.setImage(UIImage(named: "CSecureImageInvisible", in: Bundle(for: self.classForCoder), compatibleWith: nil), for: .normal)
            owerPasswordBtton.setImage(UIImage(named: "CSecureImageVisible", in: Bundle(for: self.classForCoder), compatibleWith: nil), for: .selected)
            owerPasswordBtton.frame = CGRect(x:0, y:0, width:25, height:25)
            
            textField.placeholder = NSLocalizedString("Please enter the owner's password", comment: "")
            textField.isSecureTextEntry = true
            textField.returnKeyType = .done
            textField.rightViewMode = .always
            textField.rightView = owerPasswordBtton
            
            self.textField = textField
        }
        let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
        
        let addAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default) { (action) in
            if let text = alert.textFields?.first?.text, !text.isEmpty {
                let result = pdfDocument.unlock(withPassword: text)
                if result == true {
                    if pdfDocument.permissionsStatus == .owner {
                        self.enterSecurePDF(filePath: pdfDocument.documentURL.path, password: pdfDocument.password)
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
    
    func enterPDFViewController(_ url: URL, document: CPDFDocument?) {
        var password = ""
        if let document = document {
            password = document.password ?? ""
        }
        
        let configuration = CPDFConfiguration()
        
        let thumbnail = CNavBarButtonItem(viewLeftBarButtonItem: .thumbnail)
        let back = CNavBarButtonItem(viewLeftBarButtonItem: .back)
        let search = CNavBarButtonItem(viewRightBarButtonItem: .search)
        let bota = CNavBarButtonItem(viewRightBarButtonItem: .bota)
        let more = CNavBarButtonItem(viewRightBarButtonItem: .more)
        
        configuration.showleftItems = [back, thumbnail]
        configuration.showRightItems = [search, bota, more]
        switch feature {
        case .viewer:
            configuration.enterToolModel = .viewer
        case .annotation:
            configuration.enterToolModel = .annotation
        case .form:
            configuration.enterToolModel = .form
        case .contentEdit:
            configuration.enterToolModel = .edit
        case .documentEdit:
            configuration.enterToolModel = .pageEdit
        case .watermark:
            settingWaterMark(URL: url)
            return
        case .security:
            openSecurePDF(filePath: url.path)
            return
        case .signatures:
            configuration.enterToolModel = .signature
        case .redaction:
            return
        case .compareDocument:
            return
        case .conversion:
            return
        case .compress:
            return
        case .measurement:
            return
        }
        
        configuration.showMoreItems = [.setting, .pageEdit, .info, .save, .share, .addFile]

        let pdfViewController = CPDFViewController(filePath: url.path, password: password, configuration: configuration)
        let navController = CNavigationController(rootViewController: pdfViewController)
        pdfViewController.delegate = self
        navController.modalPresentationStyle = .fullScreen
        self.present(navController, animated: true)
        
    }
    
    // MARK: - Action
    @objc func buttonItemClick_Setting(_ button: UIBarButtonItem) {
        let settingVC = CHomeSettingViewController(nibName: nil, bundle: nil)
        let navController = CNavigationController(rootViewController: settingVC)
        self.present(navController, animated: true)
    }
    
    @objc func buttonItemClicked_back(_ button: UIBarButtonItem) {
        self.dismiss(animated: true)
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
    
    @objc func buttonItemClick_Add(_ button: UIButton) {
        let openDocumentAction = UIAlertAction(title: NSLocalizedString("Open Document", comment: ""), style: .default) { _ in
            let documentTypes = ["com.adobe.pdf"]
            let documentPickerViewController = UIDocumentPickerViewController(documentTypes: documentTypes, in: .open)
            documentPickerViewController.delegate = self
            self.present(documentPickerViewController, animated: true, completion: nil)
        }
        
        let createFileAction = UIAlertAction(title: NSLocalizedString("Create a New File", comment: ""), style: .default) {_ in
            let creatPage = CHomeInsertPageViewController(nibName: nil, bundle: nil)
            creatPage.delegate = self
            let navController = CNavigationController(rootViewController: creatPage)
            let presentationController = AAPLCustomPresentationController(presentedViewController: navController, presenting: self)
            navController.transitioningDelegate = presentationController
            self.present(navController, animated: true)
        }
        
        let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style:.cancel)
        
        let alertController = UIAlertController(title: nil, message: nil, preferredStyle: .actionSheet)
        alertController.addAction(openDocumentAction)
        alertController.addAction(createFileAction)
        alertController.addAction(cancelAction)
        
        if UIDevice.current.userInterfaceIdiom == .pad {
            alertController.popoverPresentationController?.sourceView = button
            alertController.popoverPresentationController?.sourceRect = button.bounds
        }
        
        self.present(alertController, animated: true)
    }
    
    // MARK: - UITableViewDataSource
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return fileArray.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "file") as? CHomeFileTableViewCell
        if(cell == nil) {
            cell = CHomeFileTableViewCell.init(style: .default, reuseIdentifier: "file")
        }
        
        let url = fileArray[indexPath.row]
        
        var isDirectory: ObjCBool = false
        FileManager.default.fileExists(atPath: url.path, isDirectory: &isDirectory)
        let isDir = isDirectory.boolValue
        if !isDir {
            let nameTitle = (url.path as NSString?)?.lastPathComponent ?? ""
            cell?.nameTitle?.text = NSLocalizedString(nameTitle, comment: "")
            cell?.nameTitle?.adjustsFontSizeToFitWidth = true
            
            cell?.thumImage?.image = UIImage(named: "CHomeImagePDFThum", in: Bundle(for: self.classForCoder), compatibleWith: nil)
            
            if let attrib = try? FileManager.default.attributesOfItem(atPath: url.path),
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
        }
        cell?.accessoryType = .none
        
        return cell!
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: false)
        
        let url = fileArray[indexPath.row]
        
        guard let cell = tableView.cellForRow(at: indexPath) else { return }
        
        var isDirectory: ObjCBool = false
        FileManager.default.fileExists(atPath: url.path, isDirectory: &isDirectory)
        let isDir = isDirectory.boolValue
        if !isDir {
            enterPDFViewController(url, document: nil)
        }
    }
    
    func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 30.0
    }
    
    func tableView(_ tableView: UITableView, viewForHeaderInSection section: Int) -> UIView? {
        let haderView = UITableViewHeaderFooterView(frame: CGRect(x: 0, y: 5, width: self.view.frame.width, height: 20.0))
        haderView.autoresizingMask = .flexibleWidth
        
        let titlelabel = UILabel(frame: CGRect(x: 16, y: 4, width: haderView.frame.width-32, height: 20))
        titlelabel.autoresizingMask = .flexibleWidth
        titlelabel.font = UIFont.boldSystemFont(ofSize: 13)
        titlelabel.text = NSLocalizedString("Click to Open & Process", comment: "")
        haderView.addSubview(titlelabel)
        return haderView
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 58
    }
    
    // MARK: - CPDFViewBaseControllerDelete
    func PDFViewBaseControllerDissmiss(_ baseControllerDelete: CPDFViewBaseController) {
        baseControllerDelete.dismiss(animated: true)
    }
    
    // MARK: - UIDocumentPickerDelegate
    func documentPicker(_ controller: UIDocumentPickerViewController, didPickDocumentsAt urls: [URL]) {
        let url = urls.first
        let fileUrlAuthozied = url?.startAccessingSecurityScopedResource() ?? false
        if fileUrlAuthozied && url != nil {
            let pdfDocument = CPDFDocument(url: url!)
            // have open PassWord And have open+ower
            if pdfDocument != nil && pdfDocument?.isLocked == true {
                pdfDocumentPasswordVC = CDocumentPasswordViewController(document: pdfDocument!)
                pdfDocumentPasswordVC?.delegate = self
                pdfDocumentPasswordVC?.modalPresentationStyle = .fullScreen
                self.present(pdfDocumentPasswordVC!, animated: true, completion: nil)
            } else {
                enterPDFViewController(url!, document: nil)
            }
            
        }
    }
    
    private func getUniqueFilePath(filePath: String) -> String {
        var i = 0
        var isDirectory: ObjCBool = false
        var uniqueFilePath = filePath
        let fileManager = FileManager.default
        fileManager.fileExists(atPath: uniqueFilePath, isDirectory: &isDirectory)
        
        if isDirectory.boolValue {
            while fileManager.fileExists(atPath: uniqueFilePath) {
                i += 1
                uniqueFilePath = String(format: "%@(%d)", filePath, i)
            }
        } else {
            while fileManager.fileExists(atPath: uniqueFilePath) {
                i += 1
                let path = String(format: "%@(%d)", (filePath as NSString).deletingPathExtension, i)
                uniqueFilePath = (path as NSString).appendingPathExtension((filePath as NSString).pathExtension)!
            }
        }
        
        return uniqueFilePath
    }
    
    
    private func registTimer() {
        updateFolderTimer = Timer.scheduledTimer(timeInterval: 2.0, target: self, selector: #selector(updateFileManagerData), userInfo: nil, repeats: true)
        RunLoop.current.add(updateFolderTimer!, forMode: .default)
    }
    
    private func unregistTimer() {
        if updateFolderTimer?.isValid == true {
            updateFolderTimer?.invalidate()
        }
        updateFolderTimer = nil
    }
    
    @objc func updateFileManagerData() {
        reloadFileManagerData()
    }
    
    private func reloadFileManagerData() {
        searchFiles()
        tableView?.reloadData()
    }
    
    private func searchFiles() {
        var files = [URL]()
        if(path != nil) {
            let url = URL(fileURLWithPath: path!)
            let fileManager = FileManager.default
            let contents = try? fileManager.contentsOfDirectory(at: url, includingPropertiesForKeys: nil, options: [.skipsSubdirectoryDescendants, .skipsPackageDescendants, .skipsHiddenFiles])
            
            for content in contents ?? [] {
                let isDirectory = try? content.resourceValues(forKeys: [.isDirectoryKey]).isDirectory
                if let isDir = isDirectory, isDir == true {
                } else {
                    let pathExtension = content.pathExtension.lowercased()
                    if pathExtension == "pdf" {
                        files.append(content)
                    }
                }
            }
            
            fileArray.removeAll()
            fileArray.append(contentsOf: files)
        }
    }
    
    // MARK: - CPDFAddWatermarkViewControllerDelegate
    
    
    // MARK: - CDocumentPasswordViewControllerDelegate
    func documentPasswordViewControllerCancel(_ documentPasswordViewController: CDocumentPasswordViewController) {
        
    }
    
    func documentPasswordViewControllerOpen(_ documentPasswordViewController: CDocumentPasswordViewController, document: CPDFDocument) {
        if self.documentPasswordVC == documentPasswordViewController {
            if isAddWatermark {
                let addWaterMarkVC = CPDFAddWatermarkViewController.init(fileURL: document.documentURL, document: document)
                addWaterMarkVC.delegate = self
                self.navigationController?.pushViewController(addWaterMarkVC, animated: false)
            } else {
                deleteWatermarkAction(document)
            }
        } else if self.pdfDocumentPasswordVC == documentPasswordViewController {
            enterPDFViewController(document.documentURL, document: document)
        } else {
            if document.permissionsStatus == .owner {
                enterSecurePDF(filePath: document.documentURL.path, password: document.password)
            } else {
                enterPermissionPassword(pdfDocument: document)
            }
        }
    }
    
    // MARK: - CHomeInsertPageViewControllerDelegate
    
    func homeInsertPageViewController(_ homeInsertPageViewController: CHomeInsertPageViewController, URL url: URL) {
        enterPDFViewController(url, document: nil)
    }
    
}
