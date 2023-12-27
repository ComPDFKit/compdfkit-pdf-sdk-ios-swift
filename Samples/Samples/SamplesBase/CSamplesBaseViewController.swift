//
//  CSamplesBaseViewController.swift
//  Samples
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

//-----------------------------------------------------------------------------------------
// The UI, drawn using xib, is the base class for all samples classes
//-----------------------------------------------------------------------------------------

class CSamplesBaseViewController: UIViewController {
    
    @IBOutlet weak var openfileButton: UIButton!
    @IBOutlet weak var explainLabel: UILabel!
    @IBOutlet weak var commandLineTextView: UITextView!
    
    var document: CPDFDocument?

    init(document: CPDFDocument) {
        super.init(nibName: "CSamplesBaseViewController", bundle: nil)
        self.document = document
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    // MARK: - Action
    @IBAction func buttonItemClick_openFile(_ sender: Any) {
        // Action code for opening file button click
    }

    @IBAction func buttonItemClick_run(_ sender: Any) {
        // Action code for run button click
    }

}
