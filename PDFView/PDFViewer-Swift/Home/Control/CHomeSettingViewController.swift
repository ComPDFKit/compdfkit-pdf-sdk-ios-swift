//
//  CHomeSettingViewController.swift
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

class CHomeSettingViewController: UIViewController,UITableViewDelegate,UITableViewDataSource, UITextFieldDelegate {
    
    var tabview:UITableView?
    
    var footView:CHomeSettingFootView?

    override func viewDidLoad() {
        super.viewDidLoad()
        
        let closeBarItem = UIBarButtonItem(title: NSLocalizedString("Close", comment: ""), style: .done, target: self, action: #selector(buttonItemClick_Close(_:)))
        self.navigationItem.rightBarButtonItems = [closeBarItem]
        
        self.view.backgroundColor = CPDFColorUtils.CViewBackgroundColor()
        
        tabview = UITableView.init(frame: CGRect(x: 0, y: 0, width: self.view.frame.width, height: self.view.frame.height - 110), style: .plain)
        tabview?.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        tabview?.delegate = self
        tabview?.dataSource = self
        tabview?.separatorStyle = .none
        if(tabview != nil) {
            view.addSubview(tabview!)
        }
        tabview?.backgroundColor = CPDFColorUtils.CViewBackgroundColor()
        
        footView = CHomeSettingFootView(frame:CGRect(x: 0, y: self.view.frame.height - 110, width: self.view.frame.width, height: 50))
        footView?.autoresizingMask = [.flexibleWidth,.flexibleTopMargin]
        if(footView != nil) {
            view.addSubview(footView!)
        }
        
        footView?.privacyBtn?.addTarget(self, action: #selector(buttonItemClick_Privacy(_:)), for: .touchUpInside)
        footView?.serviceBtn?.addTarget(self, action: #selector(buttonItemClick_Service(_:)), for: .touchUpInside)
    }
    
    // MARK: - Action
    @objc func buttonItemClick_Close(_ button: UIBarButtonItem) {
        self.dismiss(animated: true)
    }
    
    @objc func buttonItemClick_Change(_ switchBtn: UISwitch) {
        if(switchBtn.tag == 0) {
            CPDFKitConfig.sharedInstance().setEnableLinkFieldHighlight(switchBtn.isOn)
        } else if(switchBtn.tag == 1) {
            CPDFKitConfig.sharedInstance().setEnableFormFieldHighlight(switchBtn.isOn)
        }
        
    }
    
    @objc func buttonItemClick_Privacy(_ button: UIButton) {
        if let url = URL(string: NSLocalizedString("https://www.compdf.com/privacy-policy", comment: "")) {
            UIApplication.shared.open(url)
        }
    }
    
    @objc func buttonItemClick_Service(_ button: UIButton) {
        if let url = URL(string: NSLocalizedString("https://www.compdf.com/terms-of-service", comment: "")) {
            UIApplication.shared.open(url)
        }
    }
    
    // MARK: - UITableViewDataSource
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if(section == 0) {
            return 3
        } else if(section == 1) {
            return 1
        } else {
            return 5
        }
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 3
    }
    
    func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 28.0
    }
    
    func tableView(_ tableView: UITableView, viewForHeaderInSection section: Int) -> UIView? {
        let haderView = UITableViewHeaderFooterView(frame: CGRect(x: 0, y: 0, width: self.view.frame.width, height: 28.0))
        haderView.autoresizingMask = .flexibleWidth
        let titlelabel = UILabel(frame: CGRect(x: 10, y: 4, width: haderView.frame.width-20, height: 20))
        titlelabel.font = UIFont.boldSystemFont(ofSize: 13)
        var title: String = ""
        switch section {
        case 0:
            title = NSLocalizedString("Settings", comment: "")
        case 1:
            title = NSLocalizedString("SDK Information", comment: "")
        default:
            title = NSLocalizedString("Company Information", comment: "")
        }
        titlelabel.text = title
        if #available(iOS 13.0, *) {
            titlelabel.textColor = UIColor.secondaryLabel
        } else {
            titlelabel.textColor = UIColor.init(red: 153.0/255.0, green: 153.0/255.0, blue: 153.0/255.0, alpha: 1.0)
        }
        haderView.addSubview(titlelabel)
        haderView.backgroundColor = CPDFColorUtils.CViewBackgroundColor()
        return haderView
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 44
    }
     
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var cell = tableView.dequeueReusableCell(withIdentifier: "cell") as? CHomeSettingsTableViewCell
        if(cell == nil) {
            cell = CHomeSettingsTableViewCell.init(style: .default, reuseIdentifier: "cell")
        }
        var title: String = ""

        if(indexPath.section == 0) {
            cell?.accessoryType = .none
            switch indexPath.row {
            case 0:
                title = NSLocalizedString("Highlight Links", comment: "")
                cell?.accessoryView = cell?.accessorySwitch
                cell?.accessorySwitch?.tag = indexPath.row
                cell?.accessorySwitch?.addTarget(self, action:  #selector(buttonItemClick_Change(_:)), for: .valueChanged)
                cell?.accessorySwitch?.isOn = CPDFKitConfig.sharedInstance().enableLinkFieldHighlight()
                
            case 1:
                title = NSLocalizedString("Highlight Form Fields", comment: "")
                cell?.accessoryView = cell?.accessorySwitch
                cell?.accessorySwitch?.tag = indexPath.row
                cell?.accessorySwitch?.addTarget(self, action:  #selector(buttonItemClick_Change(_:)), for: .valueChanged)
                cell?.accessorySwitch?.isOn = CPDFKitConfig.sharedInstance().enableFormFieldHighlight()
            default:
                title = NSLocalizedString("File Author", comment: "")
                cell?.accessoryView = cell?.accessoryTextField
                cell?.accessoryTextField?.addTarget(self, action: #selector(textFieldDidChange(_:)), for: .editingChanged)
                cell?.accessoryTextField?.text = CPDFKitConfig.sharedInstance().annotationAuthor()
                cell?.accessoryTextField?.returnKeyType = .done
                cell?.accessoryTextField?.delegate = self
            }
        } else if(indexPath.section == 1) {
            cell?.accessoryType = .none
            cell?.accessoryView = cell?.accessoryTitle
            title = NSLocalizedString("Version", comment: "")
            
            cell?.accessoryTitle?.text = CPDFKit.sharedInstance().versionNumber
        } else {
            cell?.accessoryView = nil
            cell?.accessoryType = .disclosureIndicator
            
            switch indexPath.row {
            case 0:
                title = NSLocalizedString("https://www.compdf.com/", comment: "")
            case 1:
                title = NSLocalizedString("About ComPDFKit", comment: "")
            case 2:
                title = NSLocalizedString("Contact Sales", comment: "")
            case 3:
                title = NSLocalizedString("Technical Support", comment: "")
            default:
                title = NSLocalizedString("support@compdf.com", comment: "")
            }
        }
        
        cell?.contentTitle?.text = title
                
        return cell!
        
    }
    
    // MARK: - UITableViewDelegate
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        self.view.endEditing(true)

        if(indexPath.section == 2) {
            switch indexPath.row {
            case 0:
                if let url = URL(string: NSLocalizedString("https://www.compdf.com/", comment: "")) {
                    UIApplication.shared.open(url)
                }
            case 1:
                if let url = URL(string: "https://www.compdf.com/company/about") {
                    UIApplication.shared.open(url)
                }
            case 2:
                if let url = URL(string: NSLocalizedString("https://www.compdf.com/contact-sales", comment: "")) {
                    UIApplication.shared.open(url)
                }
            case 3:
                if let url = URL(string: "https://www.compdf.com/support") {
                    UIApplication.shared.open(url)
                }
            default:
                let mailVC = CHomeMFMailComposeViewController.init(nibName: nil, bundle: nil)
                mailVC.setToRecipients(["support@compdf.com"])
                mailVC.setSubject(NSLocalizedString("Technical Supports", comment: ""))
                self.present(mailVC, animated: true)
            
            }
        }
    }
    
    // MARK: - UITextFieldDelegate
    @objc func textFieldDidChange(_ textField: UITextField) {
        if let text = textField.text {
            CPDFKitConfig.sharedInstance().setAnnotationAuthor(text)

        }
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.endEditing(true)
    }


}
