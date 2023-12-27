//
//  CSamplesFuctionViewController.swift
//  Samples
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//

import UIKit
import ComPDFKit

enum CSamplesType: Int {
    case bookmark
    case outline
    case pdfToImage
    case textSearch
    case annotation
    case annotationImportExport
    case interactiveForms
    case pdfPage
    case imageExtract
    case textExtract
    case documentInfo
    case watermark
    case background
    case headerFooter
    case pdfBates
    case pdfRedact
    case encry
    case pdfa
    case flattenedCopy
    case digitalSignature
}

class CSamplesFuctionViewController: UIViewController,UITableViewDataSource,UITableViewDelegate {
   
    var filePaths: [String]?
    var password: String?
    var tableView: UITableView?
    var document: CPDFDocument?
    
    var dataArray: [String] {
        return [
            NSLocalizedString("Bookmark", comment: ""),
            NSLocalizedString("Outline", comment: ""),
            NSLocalizedString("PDFToImage", comment: ""),
            NSLocalizedString("TextSearch", comment: ""),
            NSLocalizedString("Annotation", comment: ""),
            NSLocalizedString("AnnotationImportExport", comment: ""),
            NSLocalizedString("InteractiveForms", comment: ""),
            NSLocalizedString("PDFPage", comment: ""),
            NSLocalizedString("ImageExtract", comment: ""),
            NSLocalizedString("TextExtract", comment: ""),
            NSLocalizedString("DocumentInfo", comment: ""),
            NSLocalizedString("Watermark", comment: ""),
            NSLocalizedString("Background", comment: ""),
            NSLocalizedString("HeaderFooter", comment: ""),
            NSLocalizedString("Bates", comment: ""),
            NSLocalizedString("PDFRedact", comment: ""),
            NSLocalizedString("Encry", comment: ""),
            NSLocalizedString("PDFA", comment: ""),
            NSLocalizedString("FlattenedCopy", comment: ""),
            NSLocalizedString("DigitalSignature", comment: "")
        ]
    }

    
    init(filePaths: [String]?, password: String?) {
        super.init(nibName:nil, bundle: nil)
        self.filePaths = filePaths
        self.password = password
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        tableView = UITableView(frame: view.bounds, style: .plain)
        tableView?.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        tableView?.delegate = self
        tableView?.dataSource = self
        tableView?.rowHeight = UITableView.automaticDimension
        tableView?.estimatedRowHeight = 80
        tableView?.tableFooterView = UIView()
        tableView?.separatorStyle = .none
        if(tableView != nil) {
            view.addSubview(tableView!)
        }

        title = NSLocalizedString("Samples", comment: "")

        view.backgroundColor = UIColor.white

        guard let filePath = filePaths?.first as? String else { return  }
        let url = URL(fileURLWithPath: filePath)
        document = CPDFDocument(url: url)
    }
    
    
    // MARK: - UITableViewDataSource
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return dataArray.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "samples") ?? UITableViewCell(style: .default, reuseIdentifier: "samples")

        cell.textLabel?.text = dataArray[indexPath.row]

        return cell

    }
    
    // MARK: - UITableViewDelegate
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        if(self.document == nil) {
            return
        }
        
        let sampleType = CSamplesType(rawValue: indexPath.row)
        switch sampleType {
        case .bookmark:
            let bookmarkVC = CBookmarkViewController(document: document!)
            self.navigationController?.pushViewController(bookmarkVC, animated: true)
        case .outline:
            let outlineVC = COutlineViewController(document: document!)
            self.navigationController?.pushViewController(outlineVC, animated: true)
        case .pdfToImage:
            let PDFToImageVC = CPDFToImageViewController(document: document!)
            self.navigationController?.pushViewController(PDFToImageVC, animated: true)
        case .textSearch:
            let filePath = self.filePaths?[2] ?? ""
            let url = URL(fileURLWithPath: filePath )
            let document = CPDFDocument(url: url)
            if(document != nil) {
                let textSearchVC = CTextSearchViewController(document: document!)
                self.navigationController?.pushViewController(textSearchVC, animated: true)

            }
        case .annotation:
            let annotationVC = CAnnotaitonViewController(document: document!)
            self.navigationController?.pushViewController(annotationVC, animated: true)
        case .annotationImportExport:
            let filePath = self.filePaths?[3] ?? ""
            let url = URL(fileURLWithPath: filePath )
                let document = CPDFDocument(url: url)
            if(document != nil) {
                let annotationImportExportVC = CAnnotationImportExportViewController(document: document!)
                self.navigationController?.pushViewController(annotationImportExportVC, animated: true)
            }
        case .interactiveForms:
            let interactiveFormsVC = CInteractiveFormsViewController(document: document!)
            self.navigationController?.pushViewController(interactiveFormsVC, animated: true)
        case .pdfPage:
            let PDFPageVC = CPDFPageViewController(document: document!)
            self.navigationController?.pushViewController(PDFPageVC, animated: true)
        case .imageExtract:
            let imageExtractVC = CImageExtractViewController(document: document!)
            self.navigationController?.pushViewController(imageExtractVC, animated: true)
        case .textExtract:
            let textExtractVC = CTextExtractViewController(document: document!)
            self.navigationController?.pushViewController(textExtractVC, animated: true)
        case .documentInfo:
            let documentInfoVC = CDocumentInfoViewController(document: document!)
            self.navigationController?.pushViewController(documentInfoVC, animated: true)
        case .watermark:
            let watermarkVC = CWatermarkViewController(document: document!)
            self.navigationController?.pushViewController(watermarkVC, animated: true)
        case .background:
            let backgroundVC = CBackgroundViewController(document: document!)
            self.navigationController?.pushViewController(backgroundVC, animated: true)
        case .headerFooter:
            let headerfooterVC = CHeaderFooterViewController(document: document!)
            self.navigationController?.pushViewController(headerfooterVC, animated: true)
        case .pdfBates:
            let batesVC = CBatesViewController(document: document!)
            self.navigationController?.pushViewController(batesVC, animated: true)
        case .pdfRedact:
            let redactVC = CRedactViewController(document: document!)
            self.navigationController?.pushViewController(redactVC, animated: true)
        case .encry:
            let encryptVC = CEncryptViewController(document: document!)
            self.navigationController?.pushViewController(encryptVC, animated: true)
        case .pdfa:
            let PDFAVC = CPDFAViewController(document: document!)
            self.navigationController?.pushViewController(PDFAVC, animated: true)
        case .flattenedCopy:
            let filePath = self.filePaths?[3] ?? ""
            let url = URL(fileURLWithPath: filePath )
            let document = CPDFDocument(url: url)
            if(document != nil) {
                
                let flattenedCopyVC = CFlattenedCopyViewController(document: document!)
                self.navigationController?.pushViewController(flattenedCopyVC, animated: true)
            }
        case .digitalSignature:
            let filePath = self.filePaths?[0] ?? ""
            let url = URL(fileURLWithPath: filePath )
            let document = CPDFDocument(url: url)
            if(document != nil) {
                
                let digitalSignatureViewController = CDigitalSignatureViewController(document: document!)
                self.navigationController?.pushViewController(digitalSignatureViewController, animated: true)
            }
        default:
            break
        }
    }



}
