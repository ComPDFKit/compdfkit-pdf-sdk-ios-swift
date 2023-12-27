//
//  CHomeMFMailComposeViewController.swift
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
import MessageUI

class CHomeMFMailComposeViewController: MFMailComposeViewController,MFMailComposeViewControllerDelegate {

    override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: Bundle?) {
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
        
        self.mailComposeDelegate = self
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - MFMailComposeViewControllerDelegate
    func mailComposeController(_ controller: MFMailComposeViewController, didFinishWith result: MFMailComposeResult, error: Error?) {
        var tAlertMessage = ""
        
        switch result {
        case .saved:
            tAlertMessage = NSLocalizedString("The Email draft has been saved.", comment: "")
            
        case .failed:
            if error == nil {
                tAlertMessage = NSLocalizedString("Unknown Error", comment: "")
            } else {
                tAlertMessage = NSLocalizedString("An error occurred during the save operation. Unable to save the Email Draft.", comment: "")
            }
            
        case .cancelled, .sent:
            self.dismiss(animated: true, completion: nil)
            return
        @unknown default:
            break
        }
        
        let alertController = UIAlertController(title: "", message: tAlertMessage, preferredStyle: .alert)
        alertController.addAction(UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default, handler: { (action) in
            self.dismiss(animated: true, completion: nil)
        }))
        
        self.present(alertController, animated: true, completion: nil)
    }


}
