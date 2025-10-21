//
//  CHomeSettingsTableViewCell.swift
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

class CHomeSettingsTableViewCell: UITableViewCell {
    
    var contentTitle:UILabel?
    
    var accessoryTitle:UILabel?

    var accessorySwitch:UISwitch?
    
    var accessoryTextField:UITextField?
    
    // Temp
    var accessoryButton: UIButton?
    var contentSubTitle: UILabel?

    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
        contentTitle = UILabel.init(frame: CGRect(x: 20, y: (self.frame.height - 22)/2 - 11, width: self.frame.width - 20 - 65, height: 22))
        contentTitle?.font = UIFont.boldSystemFont(ofSize: 15.0)
        contentTitle?.numberOfLines = 0
        if(contentTitle != nil) {
            self.contentView.addSubview(contentTitle!)
        }
        
        contentSubTitle = UILabel.init(frame: CGRect(x: 100, y: 0, width: (contentTitle?.frame.size.width ?? 0) - 60, height: 22))
        contentSubTitle?.font = UIFont.boldSystemFont(ofSize: 9.0)
        contentSubTitle?.numberOfLines = 0
        contentSubTitle?.isHidden = true
        if(contentSubTitle != nil) {
            contentTitle?.addSubview(contentSubTitle!)
        }
        
        accessoryTitle = UILabel.init(frame: CGRect(x: 0, y: 0, width: 60, height: 22))
        accessoryTitle?.font = UIFont.boldSystemFont(ofSize: 15.0)
        accessoryTitle?.textAlignment = .right

        accessorySwitch = UISwitch(frame: CGRect(x: 0, y: 0, width: 51, height: 31))
        
        accessoryTextField = UITextField.init(frame: CGRect(x: 0, y: 0, width: 90, height: 22))
        accessoryTextField?.font = UIFont.boldSystemFont(ofSize: 15.0)
        accessoryTextField?.placeholder = NSLocalizedString("ComPDFKit", comment: "")
        accessoryTextField?.textAlignment = .right
        
        accessoryButton = UIButton.init(frame: CGRect(x: 0, y: 0, width: 70, height: 31))
        accessoryButton?.setTitle(NSLocalizedString("Update Config", comment: ""), for: .normal)
        accessoryButton?.setTitleColor(.black, for: .normal)
        accessoryButton?.titleLabel?.font = UIFont.boldSystemFont(ofSize: 15.0)
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
        
        contentTitle?.centerY = self.contentView.centerY
        contentTitle?.frame = CGRect(x: contentTitle?.frame.origin.x ?? 0, y: contentTitle?.frame.origin.y ?? 0, width: self.frame.width - 20 - 75, height: contentTitle?.frame.size.height ?? 0)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
