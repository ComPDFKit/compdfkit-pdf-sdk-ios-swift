//
//  CHomeInsertPageViewController.swift
//  ComPDFKit_Tools
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

import UIKit
import ComPDFKit
import ComPDFKit_Tools

@objc protocol CHomeInsertPageViewControllerDelegate: AnyObject {
    @objc optional func homeInsertPageViewController(_ homeInsertPageViewController: CHomeInsertPageViewController, URL url:URL)
}

class CHomeInsertPageViewController: UIViewController,UITableViewDelegate,UITableViewDataSource {
    weak var delegate: CHomeInsertPageViewControllerDelegate?
    
    var tabview:UITableView?
    
    var contenScrollView:UIScrollView?
    
    var pageHorizontalBtn:UIButton?
    var pageVerticalBtn:UIButton?
    
    var isPageVertical = true
    
    private lazy var dataArrays: [String] = {
        return [NSLocalizedString("A3(11.69x 16.54)", comment: ""),
                NSLocalizedString("A4(8.27x 11.69)", comment: ""),
                NSLocalizedString("A5(5.83x 8.27)", comment: "")]
    }()
    
    private var selectIndexPage = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.title = NSLocalizedString("Create a New File", comment: "")
        
        let creatBarItem = UIBarButtonItem(title: NSLocalizedString("OK", comment: ""), style: .done, target: self, action:  #selector(buttonItemClick_Create(_:)))
        self.navigationItem.rightBarButtonItems = [creatBarItem]
        
        let closeBarItem = UIBarButtonItem(title: NSLocalizedString("Cancel", comment: ""), style: .done, target: self, action:  #selector(buttonItemClick_Close(_:)))
        self.navigationItem.leftBarButtonItems = [closeBarItem]
        
        tabview = UITableView.init(frame: self.view.bounds, style: .plain)
        tabview?.delegate = self
        tabview?.dataSource = self
        tabview?.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        tabview?.separatorStyle = .none
        if(tabview != nil) {
            view.addSubview(tabview!)
        }
        updatePreferredContentSizeWithTraitCollection(traitCollection: traitCollection)
    }
    
    func getUniqueFilePath(filePath: String) -> String {
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
    
    
    override func willTransition(to newCollection: UITraitCollection, with coordinator: UIViewControllerTransitionCoordinator) {
        super.willTransition(to: newCollection, with: coordinator)
        updatePreferredContentSizeWithTraitCollection(traitCollection: newCollection)
    }
    
    func updatePreferredContentSizeWithTraitCollection(traitCollection: UITraitCollection) {
        preferredContentSize = CGSize(width: view.bounds.size.width, height: 228)
    }
    
    // MARK: - Action
    @objc func buttonItemClick_Create(_ button: UIBarButtonItem) {
        var pageSize = CGSize.zero
        switch selectIndexPage {
        case 0:
            pageSize.width =  (595.0/210) * 297
            pageSize.height = 420 * (595.0/210)
        case 1:
            pageSize.width =  595.0
            pageSize.height = 842.0
        default:
            pageSize.width =  148 * (595.0/210)
            pageSize.height = 210 * (595.0/210)
        }
        
        if(isPageVertical == false) {
            let z = pageSize.width
            pageSize.width = pageSize.height
            pageSize.height = z
        }
        let pdfDocument = CPDFDocument()
        
        var documentAttributes = pdfDocument!.documentAttributes()!
        let userDefaults = UserDefaults.standard
        documentAttributes[CPDFDocumentAttribute.titleAttribute] = userDefaults.string(forKey: CPDFFileAuthorKey)
        pdfDocument?.setDocumentAttributes(documentAttributes)
        
        pdfDocument?.insertPage(pageSize, at: 0)
        if (!(FileManager.default.fileExists(atPath: SAMPLESFOLDER))) {
            try? FileManager.default.createDirectory(atPath: SAMPLESFOLDER, withIntermediateDirectories: true, attributes: nil)
        }
        let docsFilePath = URL(fileURLWithPath: SAMPLESFOLDER).appendingPathComponent("/" + "Untitled" + ".pdf")
        let filePath = self.getUniqueFilePath(filePath: docsFilePath.path)
        let isSaveFontSubset = userDefaults.bool(forKey: CPDFSaveFontSubesetKey)
        let result = pdfDocument?.write(to: NSURL.fileURL(withPath: filePath), isSaveFontSubset: isSaveFontSubset)
        if(result == true) {
            self.dismiss(animated: true)
            self.delegate?.homeInsertPageViewController?(self, URL: NSURL.fileURL(withPath: filePath))
        }
        
    }
    
    @objc func buttonItemClick_Close(_ button: UIBarButtonItem) {
        self.dismiss(animated: true)
    }
    
    @objc func buttonItemClicked_Direction(_ button: UIButton) {
        pageHorizontalBtn?.backgroundColor = CPDFColorUtils.CAnnotationBarNoSelectBackgroundColor()
        pageVerticalBtn?.backgroundColor = CPDFColorUtils.CAnnotationBarNoSelectBackgroundColor()
        
        if button.tag == 0 {
            isPageVertical = true
            pageVerticalBtn?.backgroundColor = CPDFColorUtils.CAnnotationBarSelectBackgroundColor()
        } else if button.tag == 1 {
            isPageVertical = false
            pageHorizontalBtn?.backgroundColor = CPDFColorUtils.CAnnotationBarSelectBackgroundColor()
        }
    }
    
    // MARK: - UITableViewDataSource
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.dataArrays.count
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 44.0
    }
    
    func tableView(_ tableView: UITableView, viewForFooterInSection section: Int) -> UIView? {
        let haderView = UITableViewHeaderFooterView(frame: CGRect(x: 0, y: 0, width: self.view.frame.width, height: 44.0))
        haderView.autoresizingMask = .flexibleWidth
        
        let line = UIView.init(frame: CGRect(x: 16, y: 0, width: haderView.frame.width-32, height: 1))
        line.backgroundColor = UIColor.init(red: 0, green: 0, blue: 0, alpha: 0.12)
        line.autoresizingMask = .flexibleWidth
        haderView.addSubview(line)
        
        let tSelectView = UIView(frame: CGRect(x: self.view.frame.width - 72 - 10, y: 8, width: 72, height: 32))
        tSelectView.layer.cornerRadius = 5
        tSelectView.layer.masksToBounds = true
        tSelectView.autoresizingMask = [.flexibleLeftMargin]
        
        let verticalPageBtn = UIButton(frame: CGRect(x: 0, y: 0, width: 36, height: 32))
        verticalPageBtn.tag = 0
        verticalPageBtn.isSelected = false
        verticalPageBtn.backgroundColor = CPDFColorUtils.CAnnotationBarNoSelectBackgroundColor()
        verticalPageBtn.setImage(UIImage(named: "CInsertBlankPageCellVertical", in: Bundle(for: type(of: self)), compatibleWith: nil), for: .normal)
        verticalPageBtn.addTarget(self, action: #selector(buttonItemClicked_Direction(_:)), for: .touchUpInside)
        
        let horizontalPageBtn = UIButton(frame: CGRect(x: 36, y: 0, width: 36, height: 32))
        horizontalPageBtn.isSelected = false
        horizontalPageBtn.tag = 1
        horizontalPageBtn.backgroundColor = CPDFColorUtils.CAnnotationBarNoSelectBackgroundColor()
        horizontalPageBtn.setImage(UIImage(named: "CInsertBlankPageCellHorizontal", in: Bundle(for: type(of: self)), compatibleWith: nil), for: .normal)
        horizontalPageBtn.addTarget(self, action: #selector(buttonItemClicked_Direction(_:)), for: .touchUpInside)
        
        tSelectView.addSubview(horizontalPageBtn)
        tSelectView.addSubview(verticalPageBtn)
        
        pageVerticalBtn = verticalPageBtn
        pageHorizontalBtn = horizontalPageBtn
        
        if isPageVertical == false {
            pageHorizontalBtn?.backgroundColor = CPDFColorUtils.CAnnotationBarSelectBackgroundColor()
        } else {
            pageVerticalBtn?.backgroundColor = CPDFColorUtils.CAnnotationBarSelectBackgroundColor()
        }
        
        haderView.addSubview(tSelectView)
        
        let contentTitle = UILabel.init(frame: CGRect(x: 16, y: 13, width: self.view.frame.width - 72, height: 18))
        contentTitle.font = UIFont.systemFont(ofSize: 13.0)
        contentTitle.numberOfLines = 1
        contentTitle.autoresizingMask = [.flexibleWidth]
        contentTitle.text = NSLocalizedString("Page Orientation", comment: "")
        haderView.addSubview(contentTitle)
        
        return haderView
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 44
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "cell")
        if(cell == nil) {
            cell = UITableViewCell.init(style: .default, reuseIdentifier: "cell")
        }
        cell?.textLabel?.text =  self.dataArrays[indexPath.row]
        cell?.textLabel?.font = UIFont.systemFont(ofSize: 13)
        
        if(indexPath.row == selectIndexPage) {
            cell?.accessoryType = .checkmark
        } else {
            cell?.accessoryType = .none
        }
        return cell!
    }
    
    // MARK: - UITableViewDelegate
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: false)
        selectIndexPage = indexPath.row
        self.tabview?.reloadData()
    }
    
}
