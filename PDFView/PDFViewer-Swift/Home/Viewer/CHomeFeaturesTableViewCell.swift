//
//  CHomeFeaturesTableViewCell.swift
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

class CHomeFeaturesTableViewCell: UITableViewCell {
    
    var featureImage:UIImageView?
    var featureTitle:UILabel?
    var featureSubTitle:UILabel?
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
        featureImage = UIImageView.init(frame: CGRect(x: 16, y: (self.frame.height - 30)/2 - 15, width: 30, height: 30))
        featureImage?.autoresizingMask = .flexibleTopMargin
        if(featureImage != nil) {
            self.contentView.addSubview(featureImage!)
        }
        
        featureTitle = UILabel.init(frame: CGRect(x: (featureImage?.frame.maxX ?? 0) + 12, y: 0, width: self.frame.width - 62 - 12, height: 20))
        featureTitle?.font = UIFont.systemFont(ofSize: 15.0)
        featureTitle?.autoresizingMask = .flexibleWidth
        featureTitle?.numberOfLines = 1
        if(featureTitle != nil) {
            self.contentView.addSubview(featureTitle!)
        }
        
        featureSubTitle = UILabel.init(frame: CGRect(x: (featureImage?.frame.maxX ?? 0) + 12, y: 22, width: self.frame.width - 62 - 12, height: 32))
        featureSubTitle?.font = UIFont.systemFont(ofSize: 12.0)
        featureSubTitle?.autoresizingMask = .flexibleWidth
        if #available(iOS 13.0, *) {
            featureSubTitle?.textColor = UIColor.secondaryLabel
        } else {
            featureSubTitle?.textColor = UIColor.init(red: 153.0/255.0, green: 153.0/255.0, blue: 153.0/255.0, alpha: 1.0)
        }
        featureSubTitle?.numberOfLines = 2
        if(featureSubTitle != nil) {
            self.contentView.addSubview(featureSubTitle!)
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

    }

}
