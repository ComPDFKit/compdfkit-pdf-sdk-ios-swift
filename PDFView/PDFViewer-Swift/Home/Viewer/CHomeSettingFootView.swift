//
//  CHomeSettingFootView.swift
//  ComPDFKit_Tools
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

import UIKit

class CHomeSettingFootView: UIView {
    
    var footTitle:UILabel?
    var privacyBtn:UIButton?
    var serviceBtn:UIButton?
    var subView:UIView?

    override init(frame: CGRect) {
        super.init(frame: frame)
        
        footTitle = UILabel.init(frame: CGRect(x: (frame.width - 288)/2, y: 0, width: 288, height: 30))
        footTitle?.numberOfLines = 0
        footTitle?.lineBreakMode = .byWordWrapping
        footTitle?.font = UIFont.boldSystemFont(ofSize: 11.0)
        footTitle?.autoresizingMask = .flexibleLeftMargin
        footTitle?.textAlignment = .center
        if #available(iOS 13.0, *) {
            footTitle?.textColor = UIColor.secondaryLabel
        } else {
            footTitle?.textColor = UIColor.init(red: 153.0/255.0, green: 153.0/255.0, blue: 153.0/255.0, alpha: 1.0)
        }
        
        footTitle?.text = NSLocalizedString("© 2014-2026 PDF Technologies, Inc. All Rights Reserved.", comment: "")
        if(footTitle != nil) {
            self.addSubview(footTitle!)
        }
        
        subView = UIView.init(frame: CGRect(x: (frame.width - 1)/2, y: (footTitle?.frame.maxY ?? 0) + 8, width: 1, height: 15))
        if #available(iOS 13.0, *) {
            subView?.backgroundColor = UIColor.secondaryLabel
        } else {
            subView?.backgroundColor = UIColor.init(red: 153.0/255.0, green: 153.0/255.0, blue: 153.0/255.0, alpha: 1.0)
        }
        if(subView != nil) {
            self.addSubview(subView!)
        }
        
        privacyBtn = UIButton(type: .custom)
        privacyBtn?.setTitle(NSLocalizedString("Privacy Policy", comment: ""), for: .normal)
        privacyBtn?.setTitleColor(UIColor.init(red: 11/255.0, green: 85/255.0, blue: 228/255.0, alpha: 1.0), for: .normal)
        privacyBtn?.titleLabel?.font = UIFont.systemFont(ofSize: 11)
        privacyBtn?.sizeToFit()
        if(privacyBtn != nil) {
            self.addSubview(privacyBtn!)
        }

        serviceBtn = UIButton(frame: CGRect(x: (frame.width - 1)/2 + 10, y: 0, width: 100, height: 15))
        serviceBtn?.setTitle(NSLocalizedString("Service Terms", comment: ""), for: .normal)
        serviceBtn?.setTitleColor(UIColor.init(red: 11/255.0, green: 85/255.0, blue: 228/255.0, alpha: 1.0), for: .normal)
        serviceBtn?.titleLabel?.font = UIFont.systemFont(ofSize: 11)
        serviceBtn?.sizeToFit()
        if(serviceBtn != nil) {
            self.addSubview(serviceBtn!)
        }
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
        
        footTitle?.frame = CGRect(x: (frame.width - 288)/2, y: 0, width: (footTitle?.frame.size.width ?? 0), height: (footTitle?.frame.size.height ?? 0))
        let y = (footTitle?.frame.maxY ?? 0) + 4
        subView?.frame = CGRect(x: (frame.width - 1)/2, y: y, width: 1, height: 15)
        
        privacyBtn?.frame = CGRect(x: (subView?.frame.minX ?? 0) - 5 - (privacyBtn?.frame.size.width ?? 0), y: y, width: privacyBtn?.frame.size.width ?? 0, height: 15)

        serviceBtn?.frame = CGRect(x: (subView?.frame.minX ?? 0) + 5, y: y, width: serviceBtn?.frame.size.width ?? 0, height: 15)
        
    }

}
