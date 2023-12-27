//
//  CHomeSettingsTableViewCell.swift
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

class CHomeSettingsTableViewCell: UITableViewCell {
    
    var contentTitle:UILabel?
    
    var accessoryTitle:UILabel?

    var accessorySwitch:UISwitch?
    
    var accessoryTextField:UITextField?

    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
        contentTitle = UILabel.init(frame: CGRect(x: 20, y: (self.frame.height - 22)/2 - 11, width: self.frame.width - 20 - 65, height: 22))
        contentTitle?.font = UIFont.boldSystemFont(ofSize: 15.0)
        contentTitle?.numberOfLines = 1
        if(contentTitle != nil) {
            self.contentView.addSubview(contentTitle!)
        }
        
        accessoryTitle = UILabel.init(frame: CGRect(x: 0, y: 0, width: 60, height: 22))
        accessoryTitle?.font = UIFont.boldSystemFont(ofSize: 15.0)
        accessoryTitle?.textAlignment = .right

        accessorySwitch = UISwitch(frame: CGRect(x: 0, y: 0, width: 51, height: 31))
        
        accessoryTextField = UITextField.init(frame: CGRect(x: 0, y: 0, width: 90, height: 22))
        accessoryTextField?.font = UIFont.boldSystemFont(ofSize: 15.0)
        accessoryTextField?.placeholder = NSLocalizedString("ComPDFKit", comment: "")
        accessoryTextField?.textAlignment = .right
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
        
        contentTitle?.centerY = self.contentView.centerY
        contentTitle?.frame = CGRect(x: contentTitle?.frame.origin.x ?? 0, y: contentTitle?.frame.origin.y ?? 0, width: self.frame.width - 20 - 65, height: contentTitle?.frame.size.height ?? 0)
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
