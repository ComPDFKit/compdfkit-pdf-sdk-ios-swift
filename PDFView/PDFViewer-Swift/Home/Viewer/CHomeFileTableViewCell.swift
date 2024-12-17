//
//  CHomeFileTableViewCell.swift
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

class CHomeFileTableViewCell: UITableViewCell {
    var thumImage:UIImageView?
    var nameTitle:UILabel?
    var subNameTitle:UILabel?
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
        thumImage = UIImageView.init(frame: CGRect(x: 16, y: 11, width: 30, height: 30))
        if(thumImage != nil) {
            self.contentView.addSubview(thumImage!)
        }
        
        nameTitle = UILabel.init(frame: CGRect(x: (thumImage?.frame.maxX ?? 0) + 12, y: 8, width: self.frame.width - 62 - 12, height: 20))
        nameTitle?.font = UIFont.systemFont(ofSize: 17.0)
        nameTitle?.autoresizingMask = .flexibleWidth
        nameTitle?.numberOfLines = 1
        if(nameTitle != nil) {
            self.contentView.addSubview(nameTitle!)
        }
        
        subNameTitle = UILabel.init(frame: CGRect(x: (thumImage?.frame.maxX ?? 0) + 12, y: 30, width: self.frame.width - 62 - 12, height: 16))
        subNameTitle?.font = UIFont.systemFont(ofSize: 12.0)
        subNameTitle?.autoresizingMask = .flexibleWidth
        if #available(iOS 13.0, *) {
            subNameTitle?.textColor = UIColor.secondaryLabel
        } else {
            subNameTitle?.textColor = UIColor.init(red: 153.0/255.0, green: 153.0/255.0, blue: 153.0/255.0, alpha: 1.0)
        }
        subNameTitle?.numberOfLines = 2
        if(subNameTitle != nil) {
            self.contentView.addSubview(subNameTitle!)
        }
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
