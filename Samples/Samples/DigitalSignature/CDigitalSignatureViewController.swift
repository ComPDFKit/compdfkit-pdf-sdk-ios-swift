//
//  CDigitalSignatureViewController.swift
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
// This sample demonstrates the creation of digital certificates, the generation of digital
// signatures, the verification of digital certificates, the validation of digital signatures,
// the reading of digital signature information, certificate trust, and signature removal
// functionality. using API.
//-----------------------------------------------------------------------------------------

class CDigitalSignatureViewController: CSamplesBaseViewController {
    
    var isRun = false
    var commandLineStr = ""
    var digitalSignatureURL:URL?
    var certificateURL:URL?
    var deleteDigitalSignatureURL:URL?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        self.explainLabel.text = NSLocalizedString("This sample demonstrates the creation of digital certificates, the generation of digital signatures, the verification of digital certificates, the validation of digital signatures, the reading of digital signature information, certificate trust, and signature removal functionality.", comment: "")
        
        self.commandLineTextView.text = ""
        isRun = false
        commandLineStr = ""
    }
    
    // MARK: - Action
    override func buttonItemClick_openFile(_ sender: Any) {
        if isRun == true {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = openfileButton
                alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
            }
            
            let certificateAction = UIAlertAction(title: NSLocalizedString("   Certificate.pfx   ", comment: ""), style: .default) { [weak self] _ in
                // Open Certificate.pfx
                self?.openFileWithURL(url: self?.certificateURL)
            }
            
            let digitalSignatureAction = UIAlertAction(title: NSLocalizedString("   DigitalSignature.pdf   ", comment: ""), style: .default) { [weak self] _ in
                // Open DigitalSignature.pdf
                self?.openFileWithURL(url: self?.digitalSignatureURL)
            }
            
            let deleteSignatureAction = UIAlertAction(title: NSLocalizedString("   DeleteDigitalSignature.pdf   ", comment: ""), style: .default) { [weak self] _ in
                // Open DeleteDigitalSignature.pdf
                self?.openFileWithURL(url: self?.deleteDigitalSignatureURL)
            }
            
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)
            
            alertController.addAction(certificateAction)
            alertController.addAction(digitalSignatureAction)
            alertController.addAction(deleteSignatureAction)
            alertController.addAction(cancelAction)
            
            present(alertController, animated: false, completion: nil)
        } else {
            let alertController = UIAlertController(title: NSLocalizedString("Choose a file to open...", comment: ""), message: "", preferredStyle: .alert)
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                alertController.popoverPresentationController?.sourceView = openfileButton
                alertController.popoverPresentationController?.sourceRect = openfileButton.bounds
            }
            
            let noAction = UIAlertAction(title: NSLocalizedString("No files for this sample.", comment: ""), style: .default, handler: nil)
            let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: nil)

            alertController.addAction(noAction)
            alertController.addAction(cancelAction)
            present(alertController, animated: false, completion: nil)
        }
    }
    
    override func buttonItemClick_run(_ sender: Any) {
        if(document != nil) {
            isRun = true
            self.commandLineStr = self.commandLineStr + "Running FlattenedCopy sample...\n\n"
            
            generateCertificate()
            createDigitalSignature(self.document)
            verifySignatureInfo()
            verifyCertificate()
            printDigitalSignatureInfo()
            trustCertificate()
            removeDigitalSignature()
            self.commandLineStr = self.commandLineStr + "\nDone!\n"
            self.commandLineStr = self.commandLineStr + "-------------------------------------\n"
            self.commandLineTextView.text = self.commandLineStr
            
        } else {
            isRun = false
            self.commandLineStr = self.commandLineStr + "The document is null, can't open..\n\n"
            self.commandLineTextView.text = self.commandLineStr
        }
    }

    // MARK: - Samples Methods
    // <summary>
    // in the core function "CPDFPKCS12CertHelper.GeneratePKCS12Cert":
    //
    // Generate certificate
    //
    // Password: ComPDFKit
    //
    // info: /C=SG/O=ComPDFKit/D=R&D Department/CN=Alan/emailAddress=xxxx@example.com
    //
    // C=SG: This represents the country code "SG," which typically stands for Singapore.
    // O=ComPDFKit: This is the Organization (O) field, indicating the name of the organization or entity, in this case, "ComPDFKit."
    // D=R&D Department: This is the Department (D) field, indicating the specific department within the organization, in this case, "R&D Department."
    // CN=Alan: This is the Common Name (CN) field, which usually represents the name of the individual or entity. In this case, it is "Alan."
    // emailAddress=xxxx@example.com: Email is xxxx@example.com
    //
    // CPDFCertUsage.CPDFCertUsageAll: Used for both digital signing and data validation simultaneously.
    //
    // is_2048 = true: Enhanced security encryption.
    // </summary>
    
    func generateCertificate() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 1: Create a pfx format certificate for digital signature use\n"
        
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/Signature")
        
        do {
            try FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        } catch {
            commandLineStr += "Failed to create directory: \(error)\n"
            return
        }
        
        // Create a pfx format certificate
        let writeFilePath = writeDirectoryPath.appending("/Certificate.pfx")
        certificateURL = NSURL.fileURL(withPath: writeFilePath)

        var cer = [String: String]()
        cer["CN"] = "Alan"
        cer["emailAddress"] = "xxxx@example.com"
        cer["C"] = "CN"
        
        let save = CPDFSignature.generatePKCS12Cert(withInfo: cer, password: "ComPDFKit", toPath: writeFilePath, certUsage: .digSig)
        
        if save {
            commandLineStr += "File saved in \(writeFilePath)\n"
            commandLineStr += "Generate PKCS12 certificate done.\n"
        } else {
            commandLineStr += "Generate PKCS12 certificate failed.\n"
        }
        
        commandLineStr += "-------------------------------------\n"
    }
    
    // <summary>
    //
    // Adding a signature is divided into two steps:
    // creating a signature field and filling in the signature.
    //
    // Page Index: 0
    // Rect: CRect(28, 420, 150, 370)
    // Border RGB:{ 0, 0, 0 }
    // Widget Background RGB: { 150, 180, 210 }
    //
    // Text: Grantor Name
    // Content:
    //     Name: get grantor name from certificate
    //     Date: now(yyyy.mm.dd)
    //     Reason: I am the owner of the document.
    //     DN: Subject
    //     Location: Singapor
    //     IsContentAlginLeft: false
    //     IsDrawLogo: True
    //     LogoBitmap: logo.png
    //     text color RGB: { 0, 0, 0 }
    //     content color RGB: { 0, 0, 0 }
    //     Output file name: document.FileName + "_Signed.pdf"
    // </summary>
    func createDigitalSignature(_ oldDocument: CPDFDocument?) {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 2: Create a pfx format certificate for digital signature use\n"
        
        // Get Sandbox path for saving the PDF File
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/Signature")
        
        do {
            try FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)
        } catch {
            commandLineStr += "Failed to create directory: \(error)\n"
            return
        }
        
        // Save the document in the test PDF file
        let writeFilePath = writeDirectoryPath.appending("DigitalSignature.pdf")
        digitalSignatureURL = NSURL.fileURL(withPath: writeFilePath)
        oldDocument?.write(to: digitalSignatureURL)
        
        // Create a new document for the test PDF file
        let document = CPDFDocument(url: digitalSignatureURL)
        
        if let page = document?.page(at: 0) {
            let widgetAnnotation = CPDFSignatureWidgetAnnotation(document: document)
            widgetAnnotation?.setFieldName("Signature")
            widgetAnnotation?.borderWidth = 2.0
            widgetAnnotation?.bounds = CGRect(x: 28, y: 420, width: 150, height: 370)
            widgetAnnotation?.setModificationDate(NSDate() as Date)
            page.addAnnotation(widgetAnnotation)
            
            if let signatureCertificate = CPDFSignatureCertificate(pkcs12Path: certificateURL?.path, password: "ComPDFKit") {
                let signatureConfig = CPDFSignatureConfig()
                signatureConfig.image = UIImage(named: "Logo")
                signatureConfig.isContentAlginLeft = false
                signatureConfig.isDrawLogo = true
                signatureConfig.isDrawKey = true
                signatureConfig.logo = UIImage(named: "Logo")
                
                var contents: [CPDFSignatureConfigItem] = []
                if(signatureConfig.contents != nil) {
                    contents = signatureConfig.contents
                }
                
                if let issuerCN = signatureCertificate.issuerDict["CN"] as? String {
                    let configItem1 = CPDFSignatureConfigItem()
                    configItem1.key = "Digitally signed by Apple Distribution"
                    configItem1.value = NSLocalizedString(issuerCN, comment: "")
                    contents.append(configItem1)
                }
                
                let configItem2 = CPDFSignatureConfigItem()
                configItem2.key = "Date"
                let dateFormatter = DateFormatter()
                dateFormatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
                configItem2.value = dateFormatter.string(from: Date())
                contents.append(configItem2)
                
                if let subjectC = signatureCertificate.subjectDict["C"] as? String {
                    let configItem3 = CPDFSignatureConfigItem()
                    configItem3.key = "DN"
                    configItem3.value = NSLocalizedString(subjectC, comment: "")
                    contents.append(configItem3)
                }
                
                let configItem4 = CPDFSignatureConfigItem()
                configItem4.key = "ComPDFKit Version"
                if let appVersion = Bundle.main.infoDictionary?["CFBundleShortVersionString"] as? String {
                    configItem4.value = appVersion
                }
                contents.append(configItem4)
                
                let configItem5 = CPDFSignatureConfigItem()
                configItem5.key = "Reason"
                configItem5.value = NSLocalizedString("I am the owner of the document.", comment: "")
                contents.append(configItem5)
                
                let configItem6 = CPDFSignatureConfigItem()
                configItem6.key = "Location"
                configItem6.value = NSLocalizedString("<your signing location here>", comment: "")
                contents.append(configItem6)
                
                signatureConfig.contents = contents
                widgetAnnotation?.signAppearanceConfig(signatureConfig)
                
                if ((document?.writeSignature(to: digitalSignatureURL, withWidget: widgetAnnotation, pkcs12Cert: certificateURL?.path, password: "ComPDFKit", location: "<your signing location here>", reason: "I am the owner of the document.", permissions: .none)) == true) {
                    commandLineStr += "File saved in \(writeFilePath)\n"
                    commandLineStr += "Create digital signature done.\n"
                } else {
                    commandLineStr += "Create digital signature failed.\n"
                }
            }
        }
        
        commandLineStr += "-------------------------------------\n"
    }

    func verifySignatureInfo() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 3: Verify certificate\n"
        
        guard let document = CPDFDocument(url: digitalSignatureURL) else {
            commandLineStr += "Failed to open the document for verification\n"
            return
        }

        if let signatures = document.signatures() {
            for signature in signatures {
                if let signer = signature.signers.first, let certificate = signer.certificates.first {
                    var isSignVerified = true
                    var isCertTrusted = true
                    
                    // Verify the validity of the signature
                    if !signer.isCertTrusted {
                        isCertTrusted = false
                    }
                    
                    // Determine if the signature is valid and the document is unmodified
                    if !signer.isSignVerified {
                        isSignVerified = false
                    }
                    
                    if isSignVerified && isCertTrusted {
                        // Signature is valid and the certificate is trusted
                        // Perform corresponding actions
                    } else if isSignVerified && !isCertTrusted {
                        // Signature is valid but the certificate is not trusted
                        // Perform corresponding actions
                    } else if !isSignVerified && !isCertTrusted {
                        // Signature is invalid
                        // Perform corresponding actions
                    }
                    
                    commandLineStr += "Is the certificate trusted: \(isCertTrusted ? "YES" : "NO")\n"
                    commandLineStr += "Is the signature verified: \(isSignVerified ? "YES" : "NO")\n"
                }
            }
        }
        
        commandLineStr += "Verify digital signature done.\n"
        commandLineStr += "-------------------------------------\n"
    }

    func verifyCertificate() {
        if let signatureCertificate = CPDFSignatureCertificate(pkcs12Path: certificateURL?.path, password: "ComPDFKit") {
            signatureCertificate.checkIsTrusted()
            commandLineStr += "Verify certificate done.\n"
        } else {
            commandLineStr += "Failed to verify certificate\n"
        }
    }
    
    func printDigitalSignatureInfo() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 4: Print digital signature info\n"
        
        if let document = CPDFDocument(url: digitalSignatureURL) {
            if let signatures = document.signatures(), !signatures.isEmpty {
                for signature in signatures {
                    commandLineStr += "Name: \(signature.name ?? "N/A")\n"
                    commandLineStr += "Location: \(signature.location ?? "N/A")\n"
                    commandLineStr += "Reason: \(signature.reason ?? "N/A")\n"
                    commandLineStr += "Date: \(signature.date?.description ?? "N/A")\n"
                    commandLineStr += "Subject: \(signature.subFilter ?? "N/A")\n"
                }
            }
        } else {
            commandLineStr += "Failed to open the document for printing signature info\n"
        }
        
        commandLineStr += "Print digital signature info done.\n"
        commandLineStr += "-------------------------------------\n"
    }

    func trustCertificate() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 5: Trust certificate\n"
        
        if let document = CPDFDocument(url: digitalSignatureURL) {
            if let signatures = document.signatures(), !signatures.isEmpty {
                if let signature = signatures.first,
                   let signer = signature.signers.first,
                   let certificate = signer.certificates.first {
                    certificate.checkIsTrusted()
                    commandLineStr += "---Begin trusted---\n"
                    certificate.addToTrustedCertificates()
                    certificate.checkIsTrusted()
                }
            }
        } else {
            commandLineStr += "Failed to open the document for trusting the certificate\n"
        }
        
        commandLineStr += "Trust certificate done.\n"
        commandLineStr += "-------------------------------------\n"
    }

    func removeDigitalSignature() {
        commandLineStr += "-------------------------------------\n"
        commandLineStr += "Samples 6: Remove digital signature\n"
        
        let path = NSHomeDirectory()
        let writeDirectoryPath = path.appending("/Documents/Signature")
        
        if !FileManager.default.fileExists(atPath: writeDirectoryPath) {
            try? FileManager.default.createDirectory(atPath: writeDirectoryPath, withIntermediateDirectories: true, attributes: nil)

        }
        
        let writeFilePath = writeDirectoryPath.appending("/DeleteDigitalSignature.pdf")
        self.deleteDigitalSignatureURL = NSURL.fileURL(withPath: writeFilePath)

        let oldDocument = CPDFDocument(url: digitalSignatureURL)
        oldDocument?.write(to: self.deleteDigitalSignatureURL)
        
        let document = CPDFDocument(url: deleteDigitalSignatureURL)
        
        if let signatures = document?.signatures(), let signature = signatures.first {
            document?.removeSignature(signature)
        }
        
        document?.write(to: deleteDigitalSignatureURL)
    }

    func openFileWithURL(url: URL?) {
        if(url != nil) {
            let activityVC = UIActivityViewController(activityItems: [url], applicationActivities: nil)
            activityVC.definesPresentationContext = true
            
            if UIDevice.current.userInterfaceIdiom == .pad {
                activityVC.popoverPresentationController?.sourceView = openfileButton
                activityVC.popoverPresentationController?.sourceRect = openfileButton.bounds
            }
            
            present(activityVC, animated: true, completion: nil)
            
            activityVC.completionWithItemsHandler = { activityType, completed, returnedItems, activityError in
                if completed {
                    print("Success!")
                } else {
                    print("Failed Or Canceled!")
                }
            }
        }
    }



}
