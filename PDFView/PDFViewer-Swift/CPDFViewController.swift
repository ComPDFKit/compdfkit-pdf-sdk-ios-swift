//
//  CPDFViewController.swift
//  PDFViewer-Swift
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

import UIKit
import ComPDFKit
import AVFAudio
import AVFoundation
import MobileCoreServices
import ComPDFKit_Tools

open class CPDFViewController: CPDFViewBaseController,CPDFFormBarDelegate,CPDFSoundPlayBarDelegate,CPDFAnnotationBarDelegate,CPDFToolsViewControllerDelegate,CPDFNoteOpenViewControllerDelegate,CPDFEditToolBarDelegate,CPDFSignatureViewControllerDelegate,CPDFKeyboardToolbarDelegate,CPDFDigitalSignatureToolBarDelegate,CImportCertificateViewControllerDelegate,CDigitalTypeSelectViewDelegate
,CPDFSigntureVerifyViewControllerDelegate,CSignatureTypeSelectViewDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate, CreateCertificateInfoViewControllerDelegate,CPDFAddReplyViewControllerDelegate,CPDFViewReplyViewControllerDelegate {
    
    
    public var annotationBar: CPDFAnnotationToolBar?
    
    var formBar: CPDFFormToolBar?
    
    var soundPlayBar: CPDFSoundPlayBar?
    
    var annotationManage: CAnnotationManage?
    
    var toolBar: CPDFEditToolBar?
    
    var baseVC: CPDFEditViewController?
    
    var editMode: CPDFEditMode = .all
    
    var signatureAnnotation: CPDFSignatureWidgetAnnotation?
    
    var addImageRect: CGRect = CGRect.zero
    
    var addImagePage: CPDFPage?
    
    var digitalSignatureBar: CPDFDigitalSignatureToolBar?
    
    lazy var signtureViewController: CPDFSigntureViewController = {
        return CPDFSigntureViewController.init()
    }()
    
    var signtureVerifyViewController: CPDFSigntureVerifyViewController?
    
    var pkcs12DocumentPickerViewController: UIDocumentPickerViewController?
    
    var isSelctSignature: Bool = false
    
    // MARK: - ViewController Methods
    
    public override func viewDidLoad() {
        super.viewDidLoad()
        
        if let configuration = self.configuration, configuration.readerOnly {
            self.navigationController?.navigationBar.isHidden = true
            return
        }
        
        let editingConfig = CPDFEditingConfig.init()
        editingConfig.editingBorderWidth = 1.0
        editingConfig.editingOffsetGap = 5
        self.pdfListView?.editingConfig = editingConfig
        
        self.initAnnotationBar()
        self.initWithEditTool()
        self.initWithFormTool()
        self.initDigitalSignatureBar()
        
        if let availableViewModes = self.configuration?.availableViewModes, !availableViewModes.contains(self.configuration?.enterToolModel ?? .viewer), self.configuration?.enterToolModel != .pageEdit {
            self.configuration?.enterToolModel = .viewer
            if !availableViewModes.contains(.viewer) {
                self.configuration?.availableViewModes.append(.viewer)
            }
        }
        
        switch self.configuration?.enterToolModel {
        case .viewer:
            self.enterViewerMode()
        case .annotation:
            self.enterAnnotationMode()
        case .form:
            self.enterFormMode()
        case .edit:
            self.enterEditMode()
        case .pageEdit:
            self.enterViewerMode()
            self.enterPDFPageEdit()
            
        case .signature:
            enterSignatureMode()
        default:
            break
        }
        
        NotificationCenter.default.addObserver(self, selector: #selector(signatureHaveChangeDidChangeNotification(_:)), name: CSignatureHaveChangeDidChangeNotification, object: nil)
        
        NotificationCenter.default.addObserver(self, selector: #selector(signatureTrustCerDidChangeNotification(_:)), name: CSignatureTrustCerDidChangeNotification, object: nil)
        
        NotificationCenter.default.addObserver(self, selector: #selector(PDFPageDidRemoveAnnotationNotification), name: NSNotification.Name.CPDFPageDidRemoveAnnotation, object: nil)
        
        if let configuration = self.configuration, !configuration.mainToolbarVisible {
            self.navigationController?.navigationBar.isHidden = true
        }
    }
    
    func initAnnotationBar() {
        if(self.pdfListView != nil) {
            self.annotationManage = CAnnotationManage.init(pdfListView: self.pdfListView!)
            self.annotationBar = CPDFAnnotationToolBar.init(annotationManage: self.annotationManage!)
        }
        
        var height:CGFloat = 44.0
        if #available(iOS 11.0, *) {
            height += self.view.safeAreaInsets.bottom
        }
        
        self.annotationBar?.frame = CGRect(x: 0, y: self.view.frame.size.height - height, width: self.view.frame.size.width, height: height)
        self.annotationBar?.delegate = self
        self.annotationBar?.parentVC = UIApplication.presentedViewController()
        if(self.annotationBar != nil) {
            self.view.addSubview(self.annotationBar!)
        }
    }
    
    func initWithEditTool() {
        if self.toolBar == nil && self.pdfListView != nil {
            self.toolBar = CPDFEditToolBar.init(pdfView: self.pdfListView!)
        }
        
        self.toolBar?.delegate = self
        if(toolBar != nil) {
            self.view.addSubview(self.toolBar!)
        }
    }
    
    func initWithFormTool() {
        if self.formBar == nil {
            self.formBar = CPDFFormToolBar.init(annotationManage: self.annotationManage)
        }
        
        self.formBar?.delegate = self
        self.formBar?.parentVC = UIApplication.presentedViewController()
        if(formBar != nil) {
            self.view.addSubview(self.formBar!)
        }
    }
    
    func initDigitalSignatureBar() {
        self.digitalSignatureBar = CPDFDigitalSignatureToolBar(pdfListView: self.pdfListView!)
        
        var height: CGFloat = 60.0
        if #available(iOS 11.0, *) {
            height += self.view.safeAreaInsets.bottom
        }
        
        self.digitalSignatureBar?.delegate = self
    }
    
    deinit {
#if DEBUG
        print("====CPDFViewController==deinit")
#endif
    }
    
    public override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        
        if self.popMenu?.superview != nil {
            var menuCout:Float = Float(self.configuration?.showMoreItems.count ?? 0)
            let interfaceOrientation = UIApplication.shared.statusBarOrientation
            if interfaceOrientation.isLandscape {
                if menuCout > 6.0 {
                    menuCout = 6.5
                }
            }
            
            if #available(iOS 11.0, *) {
                self.popMenu?.showMenu(in: CGRect(x: self.view.frame.size.width - self.view.safeAreaInsets.right - 250, y: (self.navigationController?.navigationBar.frame)?.maxY ?? 0, width: 250, height: CGFloat(menuCout * 45) + 20))
            } else {
                self.popMenu?.showMenu(in: CGRect(x: self.view.frame.size.width - 250, y: (self.navigationController?.navigationBar.frame)?.maxY ?? 0, width: 250, height: CGFloat(menuCout * 45) + 20))
            }
        }
        
        var height: CGFloat = 44.0
        
        if #available(iOS 11.0, *) {
            height += self.view.safeAreaInsets.bottom
        }
        
        var bottomHeight: CGFloat = 0
        
        if functionTypeState == .annotation {
            if self.navigationController?.isNavigationBarHidden == false {
                
                if(self.annotationBar != nil) {
                    self.annotationBar?.frame = CGRect(x: 0, y: self.view.frame.size.height - height, width: self.view.frame.size.width, height: height)
                }
                bottomHeight = self.annotationBar?.frame.size.height ?? 0
            } else {
                if (self.pdfListView?.annotationMode != .ink && self.pdfListView?.annotationMode != .eraser) {
                    if(self.annotationBar != nil) {
                        var frame = self.annotationBar?.frame ?? CGRect.zero
                        frame.origin.y = self.view.bounds.size.height
                        self.annotationBar?.frame = frame
                    }
                    bottomHeight = 0
                } else {
                    if(self.annotationBar != nil) {
                        self.annotationBar?.frame = CGRect(x: 0, y: self.view.frame.size.height - height, width: self.view.frame.size.width, height: height)
                    }
                    bottomHeight = self.annotationBar?.frame.size.height ?? 0
                }
            }
            
        } else if functionTypeState == .edit {
            self.toolBar?.frame = CGRect(x: 0, y: self.view.frame.size.height - height, width: self.view.frame.size.width, height: height)
            bottomHeight = self.toolBar?.frame.size.height ?? 0
        } else if functionTypeState == .form {
            if self.navigationController?.isNavigationBarHidden == false {
                if(self.formBar != nil) {
                    self.formBar?.frame = CGRect(x: 0, y: self.view.frame.size.height - height, width: self.view.frame.size.width, height: height)
                }
                bottomHeight = self.formBar?.frame.size.height ?? 0
            } else {
                if(self.formBar != nil) {
                    var frame = self.formBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height
                    self.formBar?.frame = frame
                }
                bottomHeight = 0
            }
        } else if (functionTypeState == .signature) {
            if digitalSignatureBar?.superview != nil {
                if self.navigationController?.isNavigationBarHidden == false {
                    height += 14
                    digitalSignatureBar?.frame = CGRect(x: 0, y: self.view.frame.size.height - height, width: self.view.frame.size.width, height: height)
                    bottomHeight = digitalSignatureBar?.frame.height ?? 0

                } else {
                    var frame = digitalSignatureBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height
                    digitalSignatureBar?.frame = frame
                    bottomHeight = 0

                }
            }
        }
        
        height = self.navigationController?.navigationBar.frame.maxY ?? 0
        if self.signtureViewController.view.superview != nil {
            self.signtureViewController.view.frame = CGRect(x: 0, y: height, width: self.view.frame.size.width, height: 44.0)
        }
        
        if CPDFKitConfig.sharedInstance().displayDirection() == .vertical {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 10 + bottomHeight
            self.pdfListView?.documentView().contentInset = inset
        } else {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 0
            self.pdfListView?.documentView().contentInset = inset
        }
    }
    
    // MARK: - Public Methods
    
    open override func selectDocumentRefresh() {
        if self.functionTypeState == .annotation {
            self.pdfListView?.setAnnotationMode(.CPDFViewAnnotationModenone)
            self.annotationBar?.updatePropertiesButtonState()
            self.annotationBar?.reloadData()
            self.annotationBar?.updateUndoRedoState()
        } else if self.functionTypeState == .form {
            self.formBar?.initUndoRedo()
        }
    }
    
    open override func reloadDocument(withFilePath filePath: String, password: String?, completion: @escaping (Bool) -> Void) {
        navigationController?.view.isUserInteractionEnabled = false
        if loadingView.superview == nil {
            view.addSubview(self.loadingView)
        }
        self.loadingView.startAnimating()
        
        DispatchQueue.global(qos: .default).async {
            let url = URL(fileURLWithPath: filePath)
            let document = CPDFDocument(url: url)
            if document?.isLocked == true {
                document?.unlock(withPassword: password)
            }
            
            DispatchQueue.main.async {
                self.navigationController?.view.isUserInteractionEnabled = true
                self.loadingView.stopAnimating()
                self.loadingView.removeFromSuperview()
                
                if let error = document?.error, error._code != CPDFDocumentPasswordError {
                    let okAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default) { _ in
                        self.navigationController?.popViewController(animated: true)
                    }
                    let alert = UIAlertController(title: "", message: NSLocalizedString("Sorry PDF Reader Can't open this pdf file!", comment: ""), preferredStyle: .alert)
                    alert.addAction(okAction)
                    UIApplication.presentedViewController()?.present(alert, animated: true, completion: nil)
                    completion(false)
                } else {
                    self.pdfListView?.document = document
                    
                    if document?.isImageDocument() == true {
                        let okAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default) { _ in
                            self.navigationController?.popViewController(animated: true)
                        }
                        let alert = UIAlertController(title: NSLocalizedString("Warning", comment: ""), message: NSLocalizedString("The current page is scanned images that do not support adding highlights, underlines, strikeouts, and squiggly lines.", comment: ""), preferredStyle: .alert)
                        alert.addAction(okAction)
                        UIApplication.presentedViewController()?.present(alert, animated: true, completion: nil)
                    }
                    
                    completion(true)
                }
            }
        }
        
    }
    
    open override func setTitleRefresh() {
        if self.functionTypeState == .edit {
            self.enterEditMode()
        } else if self.functionTypeState == .viewer {
            self.enterViewerMode()
        } else if self.functionTypeState == .annotation {
            self.enterAnnotationMode()
        } else if self.functionTypeState == .form {
            self.enterFormMode()
        } else if self.functionTypeState == .signature {
            self.enterSignatureMode()
        }
    }
    
    func tagString() -> String {
        let formatter = DateFormatter()
        formatter.dateFormat = "YYYY-MM-ddHH:mm:ssSS"
        let dateString = formatter.string(from: Date())
        return dateString
    }
    
    func writeSignatureToWidget(_ widget: CPDFSignatureWidgetAnnotation, PKCS12Cert path: String, password: String, config: CPDFSignatureConfig, lockDocument isLock: Bool) {
        let writeDirectoryPath = SIGNATURESFOLDER
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(at: URL(fileURLWithPath: writeDirectoryPath), withIntermediateDirectories: true)
        }
    
        let documentURL = self.pdfListView?.document.documentURL
        let documentName = documentURL?.lastPathComponent.components(separatedBy: ".").first ?? ""
        let writeFilePath = writeDirectoryPath + "/" + "\(documentName)_Widget_\(tagString()).pdf"
        
        
        if FileManager.default.fileExists(atPath: writeFilePath) {
            try? FileManager.default.removeItem(at: URL(fileURLWithPath: writeFilePath))
        }
        
        var locationStr = ""
        var reasonStr = "\(NSLocalizedString("none", comment: ""))"
        
        for item in config.contents {
            if item.key == "Reason" {
                reasonStr = "\(String(describing: item.value))"
            } else if item.key == "Location" {
                locationStr = item.value
            }
        }
        
        let permissions: CPDFSignaturePermissions = isLock ? .forbidChange : .none
        
        let isSuccess = self.pdfListView?.document.writeSignature(to: URL(fileURLWithPath: writeFilePath), withWidget: widget, pkcs12Cert: path, password: password, location: locationStr, reason: reasonStr, permissions: permissions) ?? false
        
        if isSuccess {
            DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                if FileManager.default.fileExists(atPath: writeFilePath) {
                    self.reloadDocument(withFilePath: writeFilePath, password: nil, completion: { result in
                        // Handle the completion as needed
                    })
                }
            }
        }
    }
    
    // MARK: - Mode Change Methods
    
    open func enterEditMode() {
        if (self.pdfListView?.isEditFormText() == true) {
            self.pdfListView?.commitEditFormText()
        }
        self.functionTypeState = .edit

        self.selectDocumentRefresh()
        
        self.toolBar?.isHidden = false
        self.annotationBar?.isHidden = true
        self.formBar?.isHidden = true
        self.digitalSignatureBar?.isHidden = true
        self.pdfListView?.setToolModel(.edit)
        
        if CPDFEditMode.text == self.toolBar?.editToolBarSelectType {
            self.pdfListView?.beginEditingLoadType(.text)
            self.pdfListView?.setShouAddEdit(.text)
        } else if CPDFEditMode.image == self.toolBar?.editToolBarSelectType {
            self.pdfListView?.beginEditingLoadType(.image)
            self.pdfListView?.setShouAddEdit(.image)
        } else {
            self.pdfListView?.beginEditingLoadType([.text, .image, .path])
            self.pdfListView?.setShouAddEdit([])
        }
        
        self.navigationTitle = NSLocalizedString("Content Editor", comment: "")
        self.titleButton?.setTitle(self.navigationTitle as String?, for: .normal)
        
        self.pdfListView?.changeEditingLoadType([.text, .image, .path])
        self.pdfListView?.setShouAddEdit([])
        
        self.toolBar?.editToolBarSelectType = .all
        self.toolBar?.updateButtonState()
        
        var frame = self.toolBar?.frame ?? CGRect.zero
        frame.origin.y = self.view.bounds.size.height - frame.size.height
        self.toolBar?.frame = frame
        
        if digitalSignatureBar?.superview != nil {
            digitalSignatureBar?.removeFromSuperview()
        }
        
        self.viewDidLayoutSubviews()
    }
    
    open func enterAnnotationMode() {
        if (self.pdfListView?.isEditFormText() == true) {
            self.pdfListView?.commitEditFormText()
        }
        self.functionTypeState = .annotation

        self.toolBar?.isHidden = true
        self.annotationBar?.isHidden = !(self.configuration?.annotationToolbarVisible ?? true)
        self.formBar?.isHidden = true
        self.digitalSignatureBar?.isHidden = true
        
        if pdfListView?.isEditing() == true {
            if pdfListView?.isEdited() == true {
                    self.pdfListView?.commitEditing()
                    self.pdfListView?.endOfEditing()

            } else {
                    self.pdfListView?.endOfEditing()
            }
        }
        
        self.pdfListView?.setToolModel(.annotation)
        self.navigationTitle = NSLocalizedString("Annotation", comment: "")
        self.titleButton?.setTitle(self.navigationTitle as String?, for: .normal)
        
        
        var frame = self.annotationBar?.frame ?? CGRect.zero
        frame.origin.y = self.view.bounds.size.height - frame.size.height
        self.annotationBar?.frame = frame
        
        if CPDFKitConfig.sharedInstance().displayDirection() == .vertical {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 10 + (self.annotationBar?.frame.size.height ?? 0)
            self.pdfListView?.documentView().contentInset = inset
        } else {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 0
            self.pdfListView?.documentView().contentInset = inset
        }
        
        if digitalSignatureBar?.superview != nil {
            digitalSignatureBar?.removeFromSuperview()
        }
        
        self.viewDidLayoutSubviews()
    }
    
    open func enterViewerMode() {
        self.functionTypeState = .viewer
        
        self.toolBar?.isHidden = true
        self.formBar?.isHidden = true
        self.annotationBar?.isHidden = true
        self.digitalSignatureBar?.isHidden = true
        
        if pdfListView?.isEditing() == true {
            if pdfListView?.isEdited() == true {
                    self.pdfListView?.commitEditing()
                    self.pdfListView?.endOfEditing()
            } else {
                    self.pdfListView?.endOfEditing()
            }
        }
        
        self.pdfListView?.setToolModel(.viewer)
        self.navigationTitle = NSLocalizedString("Viewer", comment: "")
        self.titleButton?.setTitle(self.navigationTitle as String?, for: .normal)
        
        var frame = self.annotationBar?.frame ?? CGRect.zero
        frame.origin.y = self.view.bounds.size.height
        self.annotationBar?.frame = frame
        
        if CPDFKitConfig.sharedInstance().displayDirection() == .vertical {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 0
            self.pdfListView?.documentView().contentInset = inset
        } else {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 0
            self.pdfListView?.documentView().contentInset = inset
        }
        
        if digitalSignatureBar?.superview != nil {
            digitalSignatureBar?.removeFromSuperview()
        }
        
        self.viewDidLayoutSubviews()
    }
    
    open func enterFormMode() {
        if (self.pdfListView?.isEditFormText() == true) {
            self.pdfListView?.commitEditFormText()
        }
        self.functionTypeState = .form

        self.toolBar?.isHidden = true
        self.annotationBar?.isHidden = true
        self.formBar?.isHidden = false
        self.digitalSignatureBar?.isHidden = true
        
        if pdfListView?.isEditing() == true {
            if pdfListView?.isEdited() == true {
                    self.pdfListView?.commitEditing()
                    self.pdfListView?.endOfEditing()

            } else {
                    self.pdfListView?.endOfEditing()
            }
        }
        
        pdfListView?.setToolModel(.form)
        self.navigationTitle = NSLocalizedString("Form", comment: "")
        titleButton?.setTitle(navigationTitle as String?, for: .normal)
        
        var frame = self.formBar?.frame ?? CGRect.zero
        frame.origin.y = view.bounds.size.height - frame.size.height
        self.formBar?.frame = frame
        
        if CPDFKitConfig.sharedInstance().displayDirection() == .vertical {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 10 + (self.formBar?.frame.size.height ?? 0)
            self.pdfListView?.documentView().contentInset = inset
        } else {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 0
            self.pdfListView?.documentView().contentInset = inset
        }
        
        if digitalSignatureBar?.superview != nil {
            digitalSignatureBar?.removeFromSuperview()
        }
        
        self.viewDidLayoutSubviews()
    }
    
    open func enterSignatureMode() {
        if (self.pdfListView?.isEditFormText() == true) {
            self.pdfListView?.commitEditFormText()
        }
        self.functionTypeState = .signature

        self.toolBar?.isHidden = true
        self.formBar?.isHidden = true
        self.annotationBar?.isHidden = true
        self.digitalSignatureBar?.isHidden = false
        
        if pdfListView?.isEditing() == true {
            if pdfListView?.isEdited() == true {
                    self.pdfListView?.commitEditing()
                    self.pdfListView?.endOfEditing()

            } else {
                    self.pdfListView?.endOfEditing()
            }
        }
        
        if isSelctSignature {
            pdfListView?.setToolModel(.form)
        } else {
            pdfListView?.setToolModel(.viewer)
        }
        
        self.digitalSignatureBar?.updateButtonState()
        
        if digitalSignatureBar != nil {
            view.addSubview(digitalSignatureBar!)
        }
        
        if self.digitalSignatureBar?.superview != nil {
            self.digitalSignatureBar?.updateStatusWith(signatures: self.signatures)
        }
        
        navigationTitle = NSLocalizedString("Signatures", comment: "")
        titleButton?.setTitle(navigationTitle as String?, for: .normal)
        
        var tPosY: CGFloat = 0
        var tBottomY: CGFloat = 0
        var frame = digitalSignatureBar?.frame ?? .zero
        frame.origin.y = view.bounds.size.height - frame.size.height
        digitalSignatureBar?.frame = frame
        
        tBottomY = digitalSignatureBar?.frame.size.height ?? 0
        if let signtureViewControllerView = signtureViewController.view {
            if signtureViewControllerView.frame.height > 44.0 {
                tPosY = 0
            } else {
                tPosY = signtureViewControllerView.frame.height
            }
           
        }
        
        if CPDFKitConfig.sharedInstance().displayDirection() == .vertical {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 10 + tBottomY
            inset.top = tPosY
            self.pdfListView?.documentView().contentInset = inset
        } else {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 0
            self.pdfListView?.documentView().contentInset = inset
        }
        
    }
    
    override public func enterPDFSnipImageMode() {
        super.enterPDFSnipImageMode()
        self.pdfListView?.scrollEnabled = false
        
        if .annotation == functionTypeState {
            if !(self.navigationController?.isNavigationBarHidden ?? false) {
                self.navigationController?.setNavigationBarHidden(true, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.annotationBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height
                    self.annotationBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 0.0
                    self.annotationBar?.topToolBar?.alpha = 0.0
                    self.annotationBar?.drawPencilFuncView?.alpha = 0.0
                    
                    self.searchToolbar?.alpha = 0.0
                    
                    if self.signtureViewController.view.superview != nil {
                        self.signtureViewController.view?.alpha = 0.0
                    }
                }
            }
        } else if(.form == functionTypeState) {
            if !(self.navigationController?.isNavigationBarHidden ?? false) {
                self.navigationController?.setNavigationBarHidden(true, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.formBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height
                    self.formBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 0.0
                    
                    self.searchToolbar?.alpha = 0.0
                    if self.signtureViewController.view.superview != nil {
                        self.signtureViewController.view?.alpha = 0.0
                    }
                }
            }
        } else if(.signature == functionTypeState) {
            if !(self.navigationController?.isNavigationBarHidden ?? false) {
                self.navigationController?.setNavigationBarHidden(true, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.digitalSignatureBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height
                    self.digitalSignatureBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 0.0
                    self.signtureViewController.view?.alpha = 0.0
                }
                self.searchToolbar?.alpha = 0.0
            }
        } else {
            if !(self.navigationController?.isNavigationBarHidden ?? false) {
                self.navigationController?.setNavigationBarHidden(true, animated: true)
                UIView.animate(withDuration: 0.3) {
                    self.pdfListView?.pageSliderView?.alpha = 0.0
                    self.searchToolbar?.alpha = 0.0
                }
            }
        }
    }
    
    public func exitPDFSnipImageMode() {
        self.pdfListView?.exitSnipImage()
    }
    
    public func enterPrintState() {
       let printController = UIPrintInteractionController.shared
       
       let printInfo = UIPrintInfo(dictionary: nil)
       printInfo.outputType = .general
       printController.printInfo = printInfo
       
        printController.printingItem = self.pdfListView?.document.documentURL
       
       printController.present(animated: true, completionHandler: nil)
    }
    
    // MARK: - Action
    
    @objc open override func buttonItemClicked_Bota(_ button: UIButton?) {
        let navArrays: [CPDFBOTATypeState] = [.CPDFBOTATypeStateOutline,
                                              .CPDFBOTATypeStateBookmark,
                                              .CPDFBOTATypeStateAnnotation]
        if(self.pdfListView != nil) {
            let botaViewController = CPDFBOTAViewController(customizeWith: self.pdfListView!, navArrays: navArrays)
            botaViewController.delegate = self
            self.navigationController?.pushViewController(botaViewController, animated: false)
        }
    }
    
    @objc open override func titleButtonClickd(_ button :UIButton) {
        if configuration?.availableViewModes.count ?? 0 < 2 {
            return
        }
        
        let toolsVc = CPDFToolsViewController(Configuration: configuration ?? CPDFConfiguration())
        toolsVc.delegate = self;
        let presentationController = AAPLCustomPresentationController.init(presentedViewController: toolsVc, presenting: self)
        toolsVc.transitioningDelegate = presentationController
        UIApplication.presentedViewController()?.present(toolsVc, animated: true)
    }
    
    open override func buttonItemClicked_thumbnail(_ sender: UIButton) {
        
        if self.pdfListView?.activeAnnotations?.count ?? 0 > 0 {
            self.pdfListView?.updateActiveAnnotations([])
            self.pdfListView?.setNeedsDisplayForVisiblePages()
        }
        
        if (self.pdfListView?.isEditing() == true) {
            DispatchQueue.global(qos: .default).async {
                if self.pdfListView?.isEdited() == true {
                    self.pdfListView?.commitEditing()
                }
                DispatchQueue.main.async {
                    self.pdfListView?.endOfEditing()
                    self.enterThumbnail()
                }
            }
        } else {
            enterThumbnail()
        }
    }
    
    open override func buttonItemClicked_Search(_ button: UIButton?) {
        super.buttonItemClicked_Search(button)
        
        self.toolBar?.isHidden = true
    }
    
    open override func buttonItemClicked_searchBack(_ button: UIButton?) {
        super.buttonItemClicked_searchBack(button)
        self.toolBar?.isHidden = false
    }
    
    open override func enterThumbnail() {
        if(self.pdfListView != nil) {
            let pageEditViewController = CPDFPageEditViewController(pdfView: self.pdfListView!)
            pageEditViewController.pageEditDelegate = self
            let navController = CNavigationController(rootViewController: pageEditViewController)
            navController.modalPresentationStyle = .fullScreen
            UIApplication.presentedViewController()?.present(navController, animated: true, completion: nil)
        }
    }
    
    func showMenuList() {
        if self.pdfListView != nil {
            let baseVC = CPDFEditViewController(pdfView: self.pdfListView!)
            baseVC.editMode = self.editMode
            
            if (self.editMode == .text || self.editMode == .image) &&
                self.pdfListView?.editStatus() != CEditingSelectState(rawValue: 0) {
                let presentationController = AAPLCustomPresentationController.init(presentedViewController: baseVC, presenting: self)
                baseVC.transitioningDelegate = presentationController
                UIApplication.presentedViewController()?.present(baseVC, animated: true, completion: nil)
                
            } else if .text == self.pdfListView?.shouAddEditAreaType() {
                baseVC.editMode = CPDFEditMode.text
                let presentationController = AAPLCustomPresentationController.init(presentedViewController: baseVC, presenting: self)
                baseVC.transitioningDelegate = presentationController
                UIApplication.presentedViewController()?.present(baseVC, animated: true, completion: nil)
            }
        }
    }
    
    // MARK: - CPDFViewDelegate
    
    open override func pdfViewPerformURL(_ pdfView: CPDFView, withContent content: String!) {
        let url = URL.init(string: content)
        if(url != nil) {
            UIApplication.shared.open(url!)
        }
    }
    
    open override func pdfViewEditingSelectStateDidChanged(_ pdfView: CPDFView) {
        if pdfView.editingArea() is CPDFEditImageArea {
            self.editMode = .image
        } else if pdfView.editingArea() is CPDFEditTextArea {
            self.editMode = .text
        }
        self.toolBar?.updateButtonState()
    }
    
    open override func pdfViewShouldBeginEditing(_ pdfView: CPDFView, textView: UITextView, for annotation: CPDFFreeTextAnnotation) {
        let keyboardToolbar = CPDFKeyboardToolbar(frame: CGRect(x: 0, y: 0, width: self.view.bounds.size.width, height: 50))
        keyboardToolbar.delegate = self
        keyboardToolbar.bindToTextView(textView)
    }
    
    open override func pdfViewEditingAddTextArea(_ pdfView: CPDFView, add page: CPDFPage, add rect: CGRect) {
        var fontColor = CPDFTextProperty.shared.fontColor
        var red: CGFloat = 0, green: CGFloat = 0, blue: CGFloat = 0, alpha: CGFloat = 0
        fontColor?.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
        fontColor = UIColor(red: red, green: green, blue: blue, alpha: CPDFTextProperty.shared.textOpacity)
            
        let cfont = CPDFFont(familyName: CPDFTextProperty.shared.fontNewFamilyName, fontStyle: CPDFTextProperty.shared.fontNewStyle)
        var font = UIFont.init(name: CPDFFont.convertAppleFont(cfont) ?? "Helvetica", size: 10)
        if font == nil {
            font = UIFont(name: "Helvetica-Oblique", size: 10)
        }
        
        let atributes = CEditAttributes()
        atributes.font = font ?? UIFont()
        atributes.fontColor = fontColor ?? .black
        atributes.isBold = false
        atributes.isItalic = false
        atributes.alignment = CPDFTextProperty.shared.textAlignment
        
        self.pdfListView?.createStringBounds(rect, with: atributes, page: page)
    }
    
    open override func pdfViewEditingAddImageArea(_ pdfView: CPDFView, add page: CPDFPage, add rect: CGRect) {
        self.addImageRect = rect
        self.addImagePage = page
        let imagePicker = UIImagePickerController()
        imagePicker.sourceType = .photoLibrary
        imagePicker.delegate = self
        UIApplication.presentedViewController()?.present(imagePicker, animated: true, completion: nil)
    }
    
    open override func pdfViewCurrentPageDidChanged(_ pdfView: CPDFView?) {
        let editingArea = pdfView?.editingArea()
        if editingArea is CPDFEditImageArea {
            self.editMode = .image
        } else if editingArea is CPDFEditTextArea {
            self.editMode = .text
        }
        
        self.toolBar?.updateButtonState()
        super.pdfViewCurrentPageDidChanged(self.pdfListView)
    }
    
    open override func pdfViewWillBeginDragging(_ pdfView: CPDFView?) {
        
    }
    
    open override func pdfViewDocumentDidLoaded(_ pdfView: CPDFView!) {
        super.pdfViewDocumentDidLoaded(pdfView)
        
        if self.digitalSignatureBar?.superview != nil {
            self.digitalSignatureBar?.updateStatusWith(signatures: self.signatures)
        }
        
        if self.signtureViewController.view.superview != nil {
            verifySignature()
        }
        
    }
    
    
    // MARK: - CPDFListViewDelegate
    
    open override func PDFListViewPerformTouchEnded(_ pdfListView: CPDFListView) {
        delegate?.PDFViewBaseControllerTouchEnded?(self)
        
        if let configuration = self.configuration, configuration.readerOnly {
            return
        }
    
        if .annotation == functionTypeState {
            if self.navigationController?.isNavigationBarHidden ?? false {
                if let configuration = self.configuration, !configuration.mainToolbarVisible {
                    self.navigationController?.setNavigationBarHidden(false, animated: false)
                } else {
                    self.navigationController?.setNavigationBarHidden(false, animated: true)
                }
            
                UIView.animate(withDuration: 0.3) {
                    var frame = self.annotationBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height - frame.size.height
                    self.annotationBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 1.0
                    self.annotationBar?.topToolBar?.alpha = 1.0
                    self.annotationBar?.drawPencilFuncView?.alpha = 1.0
                    
                    self.searchToolbar?.alpha = 1.0
                    
                    if self.signtureViewController.view.superview != nil {
                        self.signtureViewController.view?.alpha = 1.0
                    }
                }
            } else {
                self.navigationController?.setNavigationBarHidden(true, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.annotationBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height
                    self.annotationBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 0.0
                    self.annotationBar?.topToolBar?.alpha = 0.0
                    self.annotationBar?.drawPencilFuncView?.alpha = 0.0
                    
                    self.searchToolbar?.alpha = 0.0
                    
                    if self.signtureViewController.view.superview != nil {
                        self.signtureViewController.view?.alpha = 0.0
                    }
                }
            }
        } else if(.form == functionTypeState) {
            if self.navigationController?.isNavigationBarHidden ?? false {
                if let configuration = self.configuration, !configuration.mainToolbarVisible {
                    self.navigationController?.setNavigationBarHidden(false, animated: false)
                } else {
                    self.navigationController?.setNavigationBarHidden(false, animated: true)
                }
                
                UIView.animate(withDuration: 0.3) {
                    var frame = self.formBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height - frame.size.height
                    self.formBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 1.0
                    
                    self.searchToolbar?.alpha = 1.0
                    if self.signtureViewController.view.superview != nil {
                        self.signtureViewController.view?.alpha = 1.0
                    }
                }
            } else {
                self.navigationController?.setNavigationBarHidden(true, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.formBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height
                    self.formBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 0.0
                    
                    self.searchToolbar?.alpha = 0.0
                    if self.signtureViewController.view.superview != nil {
                        self.signtureViewController.view?.alpha = 0.0
                    }
                }
            }
        } else if(.signature == functionTypeState) {
            if self.navigationController?.isNavigationBarHidden ?? false {
                if let configuration = self.configuration, !configuration.mainToolbarVisible {
                    self.navigationController?.setNavigationBarHidden(false, animated: false)
                } else {
                    self.navigationController?.setNavigationBarHidden(false, animated: true)
                }
                
                UIView.animate(withDuration: 0.3) {
                    var frame = self.digitalSignatureBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height - frame.size.height
                    self.digitalSignatureBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 1.0
                    
                    self.signtureViewController.view?.alpha = 1.0
                }
                self.searchToolbar?.alpha = 1.0

            } else {
                self.navigationController?.setNavigationBarHidden(true, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.digitalSignatureBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height
                    self.digitalSignatureBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 0.0
                    self.signtureViewController.view?.alpha = 0.0
                }
                self.searchToolbar?.alpha = 0.0

            }
        } else {
            if self.navigationController?.isNavigationBarHidden ?? false {
                if let configuration = self.configuration, !configuration.mainToolbarVisible {
                    self.navigationController?.setNavigationBarHidden(false, animated: false)
                } else {
                    self.navigationController?.setNavigationBarHidden(false, animated: true)
                }
                
                UIView.animate(withDuration: 0.3) {
                    self.pdfListView?.pageSliderView?.alpha = 1.0
                    self.searchToolbar?.alpha = 1.0

                }
            } else {
                self.navigationController?.setNavigationBarHidden(true, animated: true)
                UIView.animate(withDuration: 0.3) {
                    self.pdfListView?.pageSliderView?.alpha = 0.0
                    self.searchToolbar?.alpha = 0.0
                }
            }
        }
        
        self.delegate?.PDFViewBaseController?(self, HiddenState: self.navigationController?.isNavigationBarHidden ?? false)
        
        self.view.endEditing(true)
        
        if CPDFKitConfig.sharedInstance().displayDirection() == .vertical {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 10 + (self.annotationBar?.frame.size.height ?? 0)
            self.pdfListView?.documentView().contentInset = inset
        } else {
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 0
            self.pdfListView?.documentView().contentInset = inset
        }
        self.viewDidLayoutSubviews()
        
        if let configuration = self.configuration, !configuration.mainToolbarVisible {
            self.navigationController?.navigationBar.isHidden = true
        }
    }
    
    
    open override func PDFListViewEditNote(_ pdfListView: CPDFListView, forAnnotation annotation: CPDFAnnotation) {
        if annotation is CPDFLinkAnnotation {
            self.annotationBar?.buttonItemClicked_openAnnotation(self.titleButton)
        } else if annotation is CPDFWidgetAnnotation {
            self.formBar?.buttonItemClicked_openOption(annotation as! CPDFWidgetAnnotation)
        } else {
            let rect:CGRect = self.pdfListView?.convert(annotation.bounds, from: annotation.page) ?? CGRect.zero
            let noteVC = CPDFNoteOpenViewController(annotation: annotation)
            noteVC.delegate = self
            noteVC.showViewController(self, inRect: rect)
        }
    }
    
    open override func PDFListViewChangedAnnotationType(_ pdfListView: CPDFListView, forAnnotationMode annotationMode: Int) {
        if self.pdfListView?.toolModel == .annotation {
            self.annotationBar?.reloadData()
        } else if self.pdfListView?.toolModel == .form {
            self.formBar?.reloadData()
        }
    }
    
    open override func PDFListViewPerformAddStamp(_ pdfView: CPDFListView, atPoint point: CGPoint, forPage page: CPDFPage) {
        self.annotationBar?.addStampAnnotation(withPage: page, point: point)
    }
    
    open override func PDFListViewPerformAddImage(_ pdfView: CPDFListView, atPoint point: CGPoint, forPage page: CPDFPage) {
        self.annotationBar?.addImageAnnotation(withPage: page, point: point)
    }
    
    open override func PDFListViewerTouchEndedIsAudioRecordMedia(_ pdfListView: CPDFListView) -> Bool {
        if CPDFMediaManager.sharedManager.mediaState == .audioRecord {
            return true
        }
        return false
    }
    
    open override func PDFListViewPerformCancelMedia(_ pdfView: CPDFListView, atPoint point: CGPoint, forPage page: CPDFPage) {
        CPDFMediaManager.sharedManager.mediaState = .stop
    }
    
    open override func PDFListViewPerformRecordMedia(_ pdfView: CPDFListView, atPoint point: CGPoint, forPage page: CPDFPage) {
        if  self.soundPlayBar != nil && self.soundPlayBar?.superview != nil {
            if self.soundPlayBar?.soundState == .play {
                self.soundPlayBar?.stopAudioPlay()
                self.soundPlayBar?.removeFromSuperview()
            } else if self.soundPlayBar?.soundState == .record {
                self.soundPlayBar?.stopRecord()
                self.soundPlayBar?.removeFromSuperview()
            }
        }
#if targetEnvironment(macCatalyst)
        if #available(macCatalyst 14.0, *) {
            let authStatus = AVCaptureDevice.authorizationStatus(for: .audio)
            if authStatus == .notDetermined || authStatus == .denied {
                AVCaptureDevice.requestAccess(for: .audio) { granted in
                    if granted {
                        
                    } else {
                        if let url = URL(string: UIApplication.openSettingsURLString), UIApplication.shared.canOpenURL(url) {
                            UIApplication.shared.open(url, options: [:], completionHandler: nil)
                        }
                    }
                }
            }
            
            if authStatus == .authorized {
                let pageIndex = self.pdfListView?.document.index(for: page)
                CPDFMediaManager.sharedManager.mediaState = .audioRecord
                CPDFMediaManager.sharedManager.pageNum = Int(pageIndex ?? 0)
                CPDFMediaManager.sharedManager.ptInPdf = point
                
                self.soundPlayBar = CPDFSoundPlayBar(style:self.annotationManage?.annotStyle)
                self.soundPlayBar?.delegate = self
                if(self.pdfListView != nil) {
                    self.soundPlayBar?.show(inView: self.pdfListView!, soundState: .record)
                }
                self.soundPlayBar?.startAudioRecord()
            } else {
                return
            }
        } else {
            // Fallback on earlier versions
        }
#else
        let authStatus = AVCaptureDevice.authorizationStatus(for: .audio)
        if authStatus == .notDetermined || authStatus == .denied {
            AVCaptureDevice.requestAccess(for: .audio) { granted in
                if granted {
                    
                } else {
                    if let url = URL(string: UIApplication.openSettingsURLString), UIApplication.shared.canOpenURL(url) {
                        UIApplication.shared.open(url, options: [:], completionHandler: nil)
                    }
                }
            }
        }
        
        if authStatus == .authorized {
            let pageIndex = self.pdfListView?.document.index(for: page)
            CPDFMediaManager.sharedManager.mediaState = .audioRecord
            CPDFMediaManager.sharedManager.pageNum = Int(pageIndex ?? 0)
            CPDFMediaManager.sharedManager.ptInPdf = point
            
            self.soundPlayBar = CPDFSoundPlayBar(style:self.annotationManage?.annotStyle)
            self.soundPlayBar?.delegate = self
            if(self.pdfListView != nil) {
                self.soundPlayBar?.show(inView: self.pdfListView!, soundState: .record)
            }
            self.soundPlayBar?.startAudioRecord()
        } else {
            return
        }
#endif
    }
    
    open override func PDFListViewPerformPlay(_ pdfView: CPDFListView, forAnnotation annotation: CPDFSoundAnnotation) {
        if let filePath = annotation.mediaPath() {
            let URL = URL(fileURLWithPath: filePath)
            
            self.soundPlayBar = CPDFSoundPlayBar(style:self.annotationManage?.annotStyle)
            self.soundPlayBar?.delegate = self
            if(self.pdfListView != nil) {
                self.soundPlayBar?.show(inView: self.pdfListView!, soundState: .play)
            }
            self.soundPlayBar?.setURL(URL)
            self.soundPlayBar?.startAudioPlay()
            CPDFMediaManager.sharedManager.mediaState = .videoPlaying
        }
    }
    
    open override func PDFListViewPerformSignatureWidget(_ pdfView: CPDFListView, forAnnotation annotation: CPDFSignatureWidgetAnnotation) {
        if self.pdfListView?.toolModel == .annotation {
            self.annotationBar?.openSignatureAnnotation(annotation)
        } else if self.pdfListView?.toolModel == .viewer {
            self.signatureAnnotation = annotation
            
            if let annotationSignature = annotation.signature(), let signers = annotationSignature.signers, signers.count > 0 {
                let vc = CPDFSigntureVerifyDetailsViewController()
                let nav = CNavigationController(rootViewController: vc)
                vc.signature = annotationSignature
                UIApplication.presentedViewController()?.present(nav, animated: true, completion: nil)
            } else {
                if (digitalSignatureBar?.superview) != nil {
                    signatureAnnotation = annotation
                    let signatureTypeSelectView = CSignatureTypeSelectView(frame: view.frame, height: 216.0)
                    signatureTypeSelectView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
                    signatureTypeSelectView.delegate = self
                    signatureTypeSelectView.showinView(view)
                } else {
                    signatureAnnotation = annotation
                    let signatureVC = CPDFSignatureViewController(style:nil)
                    let presentationController = AAPLCustomPresentationController(presentedViewController: signatureVC, presenting: self)
                    signatureVC.delegate = self
                    signatureVC.transitioningDelegate = presentationController
                    UIApplication.presentedViewController()?.present(signatureVC, animated: true, completion: nil)
                }
            }
        } else if self.pdfListView?.toolModel == .form {
            signatureAnnotation = annotation
            let signatureTypeSelectView = CSignatureTypeSelectView(frame: view.frame, height: 216.0)
            signatureTypeSelectView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
            signatureTypeSelectView.delegate = self
            signatureTypeSelectView.showinView(view)
        }
    }
    
    open override func PDFListViewEditProperties(_ pdfListView: CPDFListView, forAnnotation annotation: CPDFAnnotation) {
        if self.pdfListView?.toolModel == .annotation {
            self.annotationBar?.buttonItemClicked_openAnnotation(self.titleButton)
        } else if self.pdfListView?.toolModel == .form {
            self.formBar?.buttonItemClicked_open(nil)
        }
    }
    
    open override func PDFListViewContentEditProperty(_ pdfListView: CPDFListView, point: CGPoint) {
        if pdfListView.editingArea() is CPDFEditImageArea {
            self.editMode = .image
        } else if pdfListView.editingArea() is CPDFEditTextArea {
            self.editMode = .text
        }
        self.showMenuList()
        self.toolBar?.updateButtonState()
    }
    
    open override func PDFListViewPerformReply(_ pdfListView: CPDFListView, forAnnotation annotation: CPDFAnnotation) {
        self.navigationController?.setNavigationBarHidden(false, animated: false)
        UIView.animate(withDuration: 0.3) {
            var frame = self.annotationBar?.frame ?? CGRect.zero
            frame.origin.y = self.view.bounds.size.height - frame.size.height
            self.annotationBar?.frame = frame
            self.pdfListView?.pageSliderView?.alpha = 1.0
            self.annotationBar?.topToolBar?.alpha = 1.0
            self.annotationBar?.drawPencilFuncView?.alpha = 1.0
            
            self.searchToolbar?.alpha = 1.0
            
            if self.signtureViewController.view.superview != nil {
                self.signtureViewController.view?.alpha = 1.0
            }
        }
        self.viewDidLayoutSubviews()
        let addReplyViewController = CPDFAddReplyViewController(annotation: annotation)
        addReplyViewController.delegate = self
        self.navigationController?.pushViewController(addReplyViewController, animated: false)
    }
    
    open override func PDFListViewPerformViewReply(_ pdfListView: CPDFListView, forAnnotation annotation: CPDFAnnotation) {
        self.navigationController?.setNavigationBarHidden(false, animated: false)
        UIView.animate(withDuration: 0.3) {
            var frame = self.annotationBar?.frame ?? CGRect.zero
            frame.origin.y = self.view.bounds.size.height - frame.size.height
            self.annotationBar?.frame = frame
            self.pdfListView?.pageSliderView?.alpha = 1.0
            self.annotationBar?.topToolBar?.alpha = 1.0
            self.annotationBar?.drawPencilFuncView?.alpha = 1.0
            
            self.searchToolbar?.alpha = 1.0
            
            if self.signtureViewController.view.superview != nil {
                self.signtureViewController.view?.alpha = 1.0
            }
        }
        self.viewDidLayoutSubviews()
        let viewReplyViewController = CPDFViewReplyViewController(anntation: annotation)
        viewReplyViewController.delegate = self
        self.navigationController?.pushViewController(viewReplyViewController, animated: false)
    }

    open func PDFListViewExitSnip(_ pdfListView: CPDFListView) {
        self.pdfListView?.scrollEnabled = true
        
        switch self.functionTypeState {
        case .viewer:
            self.pdfListView?.setToolModel(.viewer)
        case .edit:
            self.pdfListView?.setToolModel(.edit)
        case .annotation:
            self.pdfListView?.setToolModel(.annotation)
        case .form:
            self.pdfListView?.setToolModel(.form)
        case .signature:
            if isSelctSignature {
                self.pdfListView?.setToolModel(.form)
            } else {
                self.pdfListView?.setToolModel(.viewer)
            }
        default:
            self.pdfListView?.setToolModel(.viewer)
        }
        
        if .annotation == functionTypeState {
            if self.navigationController?.isNavigationBarHidden ?? false {
                self.navigationController?.setNavigationBarHidden(false, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.annotationBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height - frame.size.height
                    self.annotationBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 1.0
                    self.annotationBar?.topToolBar?.alpha = 1.0
                    self.annotationBar?.drawPencilFuncView?.alpha = 1.0
                    
                    self.searchToolbar?.alpha = 1.0
                    
                    if self.signtureViewController.view.superview != nil {
                        self.signtureViewController.view?.alpha = 1.0
                    }
                }
            }
        } else if(.form == functionTypeState) {
            if self.navigationController?.isNavigationBarHidden ?? false {
                self.navigationController?.setNavigationBarHidden(false, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.formBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height - frame.size.height
                    self.formBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 1.0
                    
                    self.searchToolbar?.alpha = 1.0
                    if self.signtureViewController.view.superview != nil {
                        self.signtureViewController.view?.alpha = 1.0
                    }
                }
            }
        } else if(.signature == functionTypeState) {
            if self.navigationController?.isNavigationBarHidden ?? false {
                self.navigationController?.setNavigationBarHidden(false, animated: true)
                UIView.animate(withDuration: 0.3) {
                    var frame = self.digitalSignatureBar?.frame ?? CGRect.zero
                    frame.origin.y = self.view.bounds.size.height - frame.size.height
                    self.digitalSignatureBar?.frame = frame
                    self.pdfListView?.pageSliderView?.alpha = 1.0
                    
                    self.signtureViewController.view?.alpha = 1.0
                }
                self.searchToolbar?.alpha = 1.0

            }
        } else {
            if self.navigationController?.isNavigationBarHidden ?? false {
                self.navigationController?.setNavigationBarHidden(false, animated: true)
                UIView.animate(withDuration: 0.3) {
                    self.pdfListView?.pageSliderView?.alpha = 1.0
                    self.searchToolbar?.alpha = 1.0

                }
            }
        }
    }
    
    // MARK: - CPDFEditToolBarDelegate
    public func editClick(in toolBar: CPDFEditToolBar, editMode mode: Int) {
        self.editMode = CPDFEditMode(rawValue: UInt(mode)) ?? .text
    }
    
    public func undoDidClick(in toolBar: CPDFEditToolBar) {
        self.pdfListView?.editTextUndo()
    }
    
    public func redoDidClick(in toolBar: CPDFEditToolBar) {
        self.pdfListView?.editTextRedo()
    }
    
    public func propertyEditDidClick(in toolBar: CPDFEditToolBar) {
        self.showMenuList()
    }
    
    // MARK: - CPDFAddReplyViewControllerDelegate
    
    public func addReplyViewController(_ viewController: CPDFAddReplyViewController, WithAnnotation annotation: CPDFAnnotation) {
        let viewReplyViewController = CPDFViewReplyViewController(anntation: annotation)
        viewReplyViewController.delegate = self
        self.navigationController?.pushViewController(viewReplyViewController, animated: false)
    }
    
    // MARK: - CPDFViewReplyViewControllerDelegate
    
    public func viewReplyViewController(_ viewController: CPDFViewReplyViewController, deleteAnnotation annotation: CPDFAnnotation) {
        annotation.page.removeAnnotation(annotation)
        self.pdfListView?.updateActiveAnnotations([])
        self.pdfListView?.setNeedsDisplayFor(annotation.page)
    }
    
    // MARK: - CPDFPageEditViewControllerDelegate
    
    open override func pageEditViewControllerDone(_ pageEditViewController: CPDFPageEditViewController) {
        pageEditViewController.dismiss(animated: false) {
            if(pageEditViewController.isPageEdit) {
                self.reloadDocument(withFilePath: (self.filePath)!, password: self.pdfListView?.document.password) { [weak self] result in
                    self?.pdfListView?.reloadInputViews()
                    self?.selectDocumentRefresh()
                }
                self.pdfListView?.reloadInputViews()
            }
            self.delegate?.PDFViewBaseControllerPageEditBack?(self)
        }
    }
    
    open override func pageEditViewController(_ pageEditViewController: CPDFPageEditViewController, pageIndex: Int, isPageEdit: Bool) {
        pageEditViewController.dismiss(animated: true) {
            if isPageEdit {
                self.reloadDocument(withFilePath: self.filePath!, password: self.pdfListView?.document.password) { [weak self] result in
                    self?.pdfListView?.reloadInputViews()
                    self?.pdfListView?.go(toPageIndex: pageIndex, animated: false)
                    if self?.functionTypeState == .edit {
                        DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                            self?.pdfListView?.setNeedsDisplayForVisiblePages()
                        }
                    }
                }
            } else {
                self.pdfListView?.go(toPageIndex: pageIndex, animated: false)
                if self.functionTypeState == .edit {
                    DispatchQueue.main.asyncAfter(deadline: .now() + 0.3) {
                        self.pdfListView?.setNeedsDisplayForVisiblePages()
                    }
                }
            }
        }
    }
    
    // MARK: - CPDFKeyboardToolbarDelegate
    public func keyboardShouldDissmiss(_ toolbar: CPDFKeyboardToolbar) {
        self.pdfListView?.commitEditAnnotationFreeText()
        self.pdfListView?.setAnnotationMode(.CPDFViewAnnotationModenone)
        self.annotationBar?.reloadData()
        self.annotationBar?.updatePropertiesButtonState()
    }
    
    // MARK: - CPDFAnnotationBarDelegate
    public func annotationBarClick(_ annotationBar: CPDFAnnotationToolBar, clickAnnotationMode annotationMode: Int, forSelected isSelected: Bool, forButton button: UIButton) {
        if CPDFViewAnnotationMode(rawValue: annotationMode) == .ink || CPDFViewAnnotationMode(rawValue: annotationMode) == .pencilDrawing || CPDFViewAnnotationMode(rawValue: annotationMode) == .eraser {
            if isSelected {
                if CPDFViewAnnotationMode(rawValue: annotationMode) == .pencilDrawing {
                   enterPecilDrawMode()
                } else {
                   enterInkMode()
                }
                self.signtureViewController.view.isHidden = true
            } else {
                if CPDFViewAnnotationMode(rawValue: annotationMode) == .pencilDrawing {
                    exitPecilDrawMode()
                } else {
                   exitInkMode()
                }
                self.signtureViewController.view.isHidden = false
            }
        } else if CPDFViewAnnotationMode(rawValue: annotationMode) == .sound && !isSelected {
            if self.soundPlayBar?.soundState == .record {
                self.soundPlayBar?.stopRecord()
            } else if self.soundPlayBar?.soundState == .play {
                self.soundPlayBar?.stopAudioPlay()
            }
            
            if pdfListView?.annotationMode == .ink {
                exitInkMode()
            }
        } else {
            if pdfListView?.annotationMode == .ink {
                exitInkMode()
            }
        }
    }
    
    private func exitInkMode() {
        self.pdfListView?.scrollEnabled = true
        self.navigationController?.setNavigationBarHidden(false, animated: true)
        UIView.animate(withDuration: 0.3) {
            self.pdfListView?.pageSliderView?.alpha = 1.0
            self.searchToolbar?.alpha = 1.0
        }
    }
    
    private func exitPecilDrawMode() {
        self.navigationController?.setNavigationBarHidden(false, animated: true)
        UIView.animate(withDuration: 0.3) {
            var frame = self.annotationBar?.frame ?? CGRect.zero
            frame.origin.y = self.view.bounds.size.height - frame.size.height
            self.annotationBar?.frame = frame
            self.pdfListView?.pageSliderView?.alpha = 1.0
            self.searchToolbar?.alpha = 1.0
        }
    }
    
    private func enterInkMode() {
        self.navigationController?.setNavigationBarHidden(true, animated: true)
        UIView.animate(withDuration: 0.3) {
            self.pdfListView?.pageSliderView?.alpha = 0.0
            self.searchToolbar?.alpha = 0.0
        }
    }
    
    private func enterPecilDrawMode() {
        self.navigationController?.setNavigationBarHidden(true, animated: true)
        UIView.animate(withDuration: 0.3) {
            var frame = self.annotationBar?.frame ?? CGRect.zero
            frame.origin.y = self.view.bounds.size.height
            self.annotationBar?.frame = frame
            self.pdfListView?.pageSliderView?.alpha = 0.0
            self.searchToolbar?.alpha = 0.0
            var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
            inset.bottom = 0
            self.pdfListView?.documentView().contentInset = inset
        }
    }
    
    // MARK: - CPDFNoteOpenViewControllerDelegate
    
    public func getNoteOpenViewController(_ noteOpenVC: CPDFNoteOpenViewController, content: String, isDelete: Bool) {
        if isDelete {
            if noteOpenVC.annotation is CPDFTextAnnotation &&  noteOpenVC.annotation?.page != nil {
                noteOpenVC.annotation?.page?.removeAnnotation(noteOpenVC.annotation)
                self.pdfListView?.setNeedsDisplayFor(noteOpenVC.annotation?.page)
                if self.pdfListView?.activeAnnotations?.contains(noteOpenVC.annotation ?? CPDFAnnotation()) == true {
                    var activeAnnotations:[CPDFAnnotation] = self.pdfListView?.activeAnnotations ?? []
                    if let index = activeAnnotations.firstIndex(of: noteOpenVC.annotation ?? CPDFAnnotation()) {
                        activeAnnotations.remove(at: index)
                        self.pdfListView?.updateActiveAnnotations(activeAnnotations)
                    }
                }
            } else {
                noteOpenVC.annotation?.contents = ""
            }
            
        } else {
            if let markupAnnotation = noteOpenVC.annotation as? CPDFMarkupAnnotation {
                markupAnnotation.contents = content
            } else if let textAnnotation = noteOpenVC.annotation as? CPDFTextAnnotation {
                if !content.isEmpty {
                    textAnnotation.contents = content
                } else {
                    if self.pdfListView?.activeAnnotations?.contains(noteOpenVC.annotation ?? CPDFAnnotation()) == true {
                        self.pdfListView?.updateActiveAnnotations([])
                    }
                    
                    if noteOpenVC.annotation?.page != nil {
                        noteOpenVC.annotation?.page?.removeAnnotation(noteOpenVC.annotation ?? CPDFAnnotation())
                        self.pdfListView?.setNeedsDisplayFor(noteOpenVC.annotation?.page)
                    }
                }
            } else {
                noteOpenVC.annotation?.contents = content
            }
        }
    }
    
    // MARK: - CPDFNoteOpenViewControllerDelegate
    public func soundPlayBarRecordFinished(_ soundPlayBar: CPDFSoundPlayBar, withFile filePath: String) {
        guard let page = self.pdfListView?.document.page(at: UInt(CPDFMediaManager.sharedManager.pageNum)) else {
            return
        }
        let annotation:CPDFSoundAnnotation = CPDFSoundAnnotation(document: self.pdfListView?.document)
        if ((annotation.setMediaPath(filePath))) {
            var bounds:CGRect = annotation.bounds
            let ptinPoint:CGPoint = CPDFMediaManager.sharedManager.ptInPdf
            
            bounds.origin.x = ptinPoint.x - bounds.size.width / 2.0
            bounds.origin.y = ptinPoint.y - bounds.size.height / 2.0
            annotation.bounds = bounds
            self.pdfListView?.addAnnotation(annotation, for: page)
        }
        CPDFMediaManager.sharedManager.mediaState = .stop
        self.pdfListView?.stopRecord()
    }
    
    public func soundPlayBarRecordCancel(_ soundPlayBar: CPDFSoundPlayBar) {
        if self.soundPlayBar?.soundState == .record {
            self.pdfListView?.stopRecord()
        }
        CPDFMediaManager.sharedManager.mediaState = .stop
    }
    
    public func soundPlayBarPlayClose(_ soundPlayBar: CPDFSoundPlayBar) {
        CPDFMediaManager.sharedManager.mediaState = .stop
    }
    
    // MARK: - Notification
    
    @objc func signatureHaveChangeDidChangeNotification(_ notification: Notification) {
        if pdfListView === notification.object as? CPDFListView {
            if let signatures = pdfListView?.document.signatures() {
                var mSignatures = [CPDFSignature]()
                for sign in signatures {
                    if sign.signers.count > 0 {
                        mSignatures.append(sign)
                    }
                }
                self.signatures = mSignatures
            }
        }
        
        if self.digitalSignatureBar?.superview != nil {
            self.digitalSignatureBar?.updateStatusWith(signatures: self.signatures)
        }
        
        if self.signtureViewController.view.superview != nil {
            verifySignature()
        }
        
    }
    
    @objc func signatureTrustCerDidChangeNotification(_ notification: Notification) {
        let signatures = pdfListView?.document.signatures()
        if let signatures = pdfListView?.document.signatures() {
            var mSignatures = [CPDFSignature]()
            for sign in signatures {
                if sign.signers.count > 0 {
                    mSignatures.append(sign)
                }
            }
            self.signatures = mSignatures
        }
        
        if self.digitalSignatureBar?.superview != nil {
            self.digitalSignatureBar?.updateStatusWith(signatures: self.signatures)
        }
        
        if self.signtureViewController.view.superview != nil {
            verifySignature()
        }
        if let signtureVerifyViewController = self.signtureVerifyViewController {
            signtureVerifyViewController.signatures = signatures ?? []
            signtureVerifyViewController.PDFListView = pdfListView
            signtureVerifyViewController.reloadData()
        }
    }
    
    @objc func PDFPageDidRemoveAnnotationNotification(notification :NSNotification) {
        if let annotation = notification.object as? CPDFAnnotation, annotation is CPDFSoundAnnotation { self.soundPlayBar?.stopAudioPlay()
            if ((self.soundPlayBar?.isDescendant(of: self.view)) != nil) {
                self.soundPlayBar?.removeFromSuperview()
            }
        } else if let annotation = notification.object as? CPDFAnnotation,
                  let signatureWidgetAnnotation = annotation as? CPDFSignatureWidgetAnnotation,
                  let signature = signatureWidgetAnnotation.signature(),
                  let page = annotation.page {
            
            pdfListView?.document.removeSignature(signature)
            
            annotation.updateAppearanceStream()
            pdfListView?.setNeedsDisplayFor(page)
            
            NotificationCenter.default.post(name: Notification.Name(CSignatureHaveChangeDidChangeNotification.rawValue), object: pdfListView)
        }
    }

    // MARK: - CPDFToolsViewControllerDelegate
    
    public func CPDFToolsViewControllerDismiss(_ viewController: CPDFToolsViewController, selectItemAtIndex selectIndex: CPDFToolFunctionTypeState) {
        if selectIndex == .viewer {
            self.enterViewerMode()
        } else if selectIndex == .edit {
            self.enterEditMode()
        } else if selectIndex == .annotation {
            self.enterAnnotationMode()
        } else if selectIndex == .form {
            self.formBar?.updateStatus()
            self.enterFormMode()
        } else if selectIndex == .signature {
            self.enterSignatureMode()
        }
        self.pdfListView?.setNeedsLayout()
        self.pdfListView?.pageSliderView?.reloadData()

    }
    
    // MARK: - CPDFBOTAViewControllerDelegate
    
    open override func botaViewControllerDismiss(_ botaViewController: CPDFBOTAViewController) {
    }
    
    // MARK: - CPDFSignatureViewControllerDelegate
    
    public func signatureViewControllerDismiss(_ signatureViewController: CPDFSignatureViewController) {
        self.signatureAnnotation = nil;
        
    }
    
    public func signatureViewController(_ signatureViewController: CPDFSignatureViewController, image: UIImage) {
        if (self.signatureAnnotation != nil) {
            self.signatureAnnotation?.sign(with: image)
            self.pdfListView?.setNeedsDisplayFor(self.signatureAnnotation?.page)
            self.signatureAnnotation = nil;
        }
    }
    
    // MARK: - imagePickerDelegate
    
    public func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        var url: URL? = nil
        if #available(iOS 11.0, *) {
            url = info[UIImagePickerController.InfoKey.imageURL] as? URL
        } else {
            url = info[UIImagePickerController.InfoKey.mediaURL] as? URL
        }
        
        var image: UIImage? = nil
        if let urlPath = url?.path {
            image = UIImage(contentsOfFile: urlPath)
        }
        
        var img_width: CGFloat = 0
        var img_height: CGFloat = 0
        var scaled_width: CGFloat = 149
        var scaled_height: CGFloat = 210
        
        if let orientation = image?.imageOrientation, orientation != .up, let originalImage = image {
            UIGraphicsBeginImageContext(originalImage.size)
            originalImage.draw(in: CGRect(x: 0, y: 0, width: originalImage.size.width, height: originalImage.size.height))
            image = UIGraphicsGetImageFromCurrentImageContext()
            UIGraphicsEndImageContext()
            
            img_width = image?.size.width ?? 0
            img_height = image?.size.height ?? 0
        } else {
            img_width = image?.size.width ?? 0
            img_height = image?.size.height ?? 0
        }
        
        let scaled = min(scaled_width / img_width, scaled_height / img_height)
        scaled_height = img_height * scaled
        scaled_width = img_width * scaled
        
        let rect = CGRect(x: self.addImageRect.origin.x, y: self.addImageRect.origin.y - scaled_height, width: scaled_width, height: scaled_height)
        self.pdfListView?.createEmptyImage(rect, page: self.addImagePage, path: url?.path)
        
        picker.dismiss(animated: true, completion: nil)
    }
    
    // MARK: - UIDocumentPickerDelegate
    
    open override func documentPicker(_ controller: UIDocumentPickerViewController, didPickDocumentsAt urls: [URL]) {
        if pkcs12DocumentPickerViewController == controller {
            if let fileUrl = urls.first, fileUrl.startAccessingSecurityScopedResource() {
                let fileCoordinator = NSFileCoordinator()
                var error: NSError?
                
                fileCoordinator.coordinate(readingItemAt: fileUrl, options: [], error: &error) { newURL in
                    let documentFolder = NSHomeDirectory() + "/Documents/Files"
                    
                    if !FileManager.default.fileExists(atPath: documentFolder) {
                        try? FileManager.default.createDirectory(at: URL(fileURLWithPath: documentFolder), withIntermediateDirectories: true, attributes: nil)
                    }
                    
                    let documentPath = documentFolder + "/" + newURL.lastPathComponent
                    
                    if !FileManager.default.fileExists(atPath: documentPath) {
                        try? FileManager.default.copyItem(at: newURL, to: URL(fileURLWithPath: documentPath))
                    }
                    
                    let url = URL(fileURLWithPath: documentPath)
                    let certificateViewController = CImportCertificateViewController(p12FilePath: url, annotation: self.signatureAnnotation ?? CPDFSignatureWidgetAnnotation())
                    certificateViewController.delegate = self
                    UIApplication.presentedViewController()?.present(certificateViewController, animated: true, completion: nil)
                }
                
                fileUrl.stopAccessingSecurityScopedResource()
            }
        } else if documentPickerViewController == controller {
            let fileUrlAuthozied = urls.first?.startAccessingSecurityScopedResource() ?? false
            if fileUrlAuthozied {
                if self.pdfListView!.isEditing() == true {
                    DispatchQueue.global(qos: .default).async {
                        if self.pdfListView?.isEdited() == true {
                            self.pdfListView?.commitEditing()
                        }
                        DispatchQueue.main.async {
                            self.pdfListView?.endOfEditing()
                            DispatchQueue.global(qos: .default).async {
                                if self.pdfListView?.document.isModified() == true {
                                    let userDefaults = UserDefaults.standard
                                    let isSaveFontSubset = userDefaults.bool(forKey: CPDFSaveFontSubesetKey)
                                    self.pdfListView?.document.write(to: self.pdfListView!.document.documentURL, isSaveFontSubset: isSaveFontSubset)
                                }
                                DispatchQueue.main.async {
                                    self.openFile(with: urls)
                                    
                                    if self.signtureViewController.view.superview != nil {
                                        self.signtureViewController.view.removeFromSuperview()
                                    }
                                    
                                }
                            }
                        }
                    }
                } else {
                    DispatchQueue.global(qos: .default).async {
                        if self.pdfListView?.document.isModified() == true {
                            let userDefaults = UserDefaults.standard
                            let isSaveFontSubset = userDefaults.bool(forKey: CPDFSaveFontSubesetKey)
                            self.pdfListView?.document.write(to: self.pdfListView!.document.documentURL, isSaveFontSubset: isSaveFontSubset)
                        }
                        DispatchQueue.main.async {
                            self.openFile(with: urls)
                            
                            if self.signtureViewController.view.superview != nil {
                                self.signtureViewController.view.removeFromSuperview()
                            }
                        }
                    }
                }
            }
        }
    }
    
    // MARK: - CDigitalTypeSelectViewDelegate
    
    @objc public func CDigitalTypeSelectViewUse(_ digitalTypeSelectView: CDigitalTypeSelectView) {
        DispatchQueue.global(qos: .default).async {
            DispatchQueue.main.async {
                let documentTypes = [kUTTypePKCS12 as String]
                self.pkcs12DocumentPickerViewController = UIDocumentPickerViewController(documentTypes: documentTypes, in: .open)
                self.pkcs12DocumentPickerViewController?.delegate = self
                if self.pkcs12DocumentPickerViewController != nil {
                    UIApplication.presentedViewController()?.present(self.pkcs12DocumentPickerViewController!, animated: true, completion: nil)
                }
            }
        }
    }
    
    @objc public func CDigitalTypeSelectViewCreate(_ digitalTypeSelectView: CDigitalTypeSelectView) {
        let createCertificateViewController = CCreateCertificateInfoViewController(annotation: signatureAnnotation ?? CPDFSignatureWidgetAnnotation())
        createCertificateViewController.delegate = self
        UIApplication.presentedViewController()?.present(createCertificateViewController, animated: true)
    }
    
    // MARK: - CImportCertificateViewControllerDelegate
    
    public func importCertificateViewControllerSave(_ importCertificateViewController: CImportCertificateViewController, PKCS12Cert path: String, password: String, config: CPDFSignatureConfig) {
        self.dismiss(animated: false) {
            self.writeSignatureToWidget(self.signatureAnnotation ?? CPDFSignatureWidgetAnnotation(), PKCS12Cert: path, password: password, config: config, lockDocument: true)
        }
    }
    
    public func importCertificateViewControllerCancel(_ importCertificateViewController: CImportCertificateViewController) {
        self.signatureAnnotation?.reset()
        self.signatureAnnotation?.updateAppearanceStream()
        self.dismiss(animated: false)
        pdfListView?.setNeedsDisplayFor(self.signatureAnnotation?.page)
        
        let signatureTypeSelectView = CSignatureTypeSelectView(frame: view.frame, height: 216.0)
        signatureTypeSelectView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        signatureTypeSelectView.delegate = self
        signatureTypeSelectView.showinView(view)
    }
    
    // MARK: - CCreateCertificateInfoViewControllerDelegate
    
    public func createCertificateInfoViewControllerCancel(_ createCertificateInfoViewController: CCreateCertificateInfoViewController) {
        self.signatureAnnotation?.reset()
        self.signatureAnnotation?.updateAppearanceStream()
        self.dismiss(animated: false)
        pdfListView?.setNeedsDisplayFor(self.signatureAnnotation?.page)
        
        let signatureTypeSelectView = CSignatureTypeSelectView(frame: view.frame, height: 216.0)
        signatureTypeSelectView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        signatureTypeSelectView.delegate = self
        signatureTypeSelectView.showinView(view)
    }
    
    public func createCertificateInfoViewControllerSave(_ createCertificateInfoViewController: CCreateCertificateInfoViewController, PKCS12Cert path: String, password: String, config: CPDFSignatureConfig) {
        self.dismiss(animated: false) {
            self.pdfListView?.setNeedsDisplayFor(self.signatureAnnotation?.page)
            self.writeSignatureToWidget(self.signatureAnnotation ?? CPDFSignatureWidgetAnnotation(), PKCS12Cert: path, password: password, config: config, lockDocument: true)
        }
    }
    
    func verifySignature() {
        let signatures = self.signatures ?? []
        
        if signatures.count > 0 {
            self.navigationController?.view.isUserInteractionEnabled = false
            
            DispatchQueue.global(qos: .default).async {
                for sign in signatures {
                    sign.verifySignature(with: self.pdfListView?.document)
                }
                
                DispatchQueue.main.async {
                    self.navigationController?.view.isUserInteractionEnabled = true
                    let blockSelf = self
                    
                    self.signtureViewController.updateCertState(signatures)
                    self.signtureViewController.callback = {
                        let signtureVerifyViewController = CPDFSigntureVerifyViewController()
                        signtureVerifyViewController.delegate = blockSelf
                        signtureVerifyViewController.signatures = signatures
                        signtureVerifyViewController.PDFListView = blockSelf.pdfListView
                        let nav = CNavigationController(rootViewController: signtureVerifyViewController)
                        UIApplication.presentedViewController()?.present(nav, animated: true, completion: nil)
                    }
                    
                    if self.signtureViewController.view.superview == nil {
                        self.view.addSubview(self.signtureViewController.view ?? UIView())
                        self.view.bringSubviewToFront(self.signtureViewController.view ?? UIView())
                    }
                    let height = self.navigationController?.navigationBar.frame.maxY ?? 0
                    self.signtureViewController.view.frame = CGRect(x: 0, y: height, width: self.view.frame.size.width, height: 44.0)
                    var tPosY: CGFloat = 0
                    if self.signtureViewController.view.superview != nil {
                        tPosY = self.signtureViewController.view.frame.size.height
                    }
                    
                    if .vertical == CPDFKitConfig.sharedInstance().displayDirection() {
                        var inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
                        inset.top = tPosY
                        self.pdfListView?.documentView().contentInset = inset
                    } else {
                        let inset:UIEdgeInsets = self.pdfListView?.documentView().contentInset ?? UIEdgeInsets.zero
                        self.pdfListView?.documentView().contentInset = inset
                    }
                }
            }
        } else {
            if self.signtureViewController.view.superview != nil {
                self.signtureViewController.view.removeFromSuperview()
    
            }
        }
    }
    
    // MARK: - CPDFSignatureViewControllerDelegate
    
    public func verifySignatureBar(_ pdfSignatureBar: CPDFDigitalSignatureToolBar, sourceButton: UIButton) {
        verifySignature()
    }
    
    public func addSignatureBar(_ pdfSignatureBar: CPDFDigitalSignatureToolBar, sourceButton: UIButton) {
        self.isSelctSignature = sourceButton.isSelected
        
        if self.isSelctSignature {
            pdfListView?.setToolModel(.form)
            pdfListView?.setAnnotationMode(.formModeSign)
        } else {
            pdfListView?.setToolModel(.viewer)
        }
    }
    
    // MARK: - CSignatureTypeSelectViewDelegate
    
    public func signatureTypeSelectViewElectronic(_ signatureTypeSelectView: CSignatureTypeSelectView) {
        let signatureVC = CPDFSignatureViewController(style:nil)
        let presentationController = AAPLCustomPresentationController(presentedViewController: signatureVC, presenting: self)
        signatureVC.delegate = self
        signatureVC.transitioningDelegate = presentationController
        UIApplication.presentedViewController()?.present(signatureVC, animated: true, completion: nil)
    }
    
    public func signatureTypeSelectViewDigital(_ signatureTypeSelectView: CSignatureTypeSelectView) {
        let digitalTypeSelect = CDigitalTypeSelectView.loadFromNib()
        digitalTypeSelect.delegate = self
        digitalTypeSelect.frame = view.frame
        digitalTypeSelect.show(in: view)
    }
    
}
