
Pod::Spec.new do |spec|

  spec.name         = "ComPDFKit"
  spec.version      = "1.13.0"
  spec.summary      = "Comprehensiven iOS PDF SDK solutions for developers."
  spec.description  = <<-DESC
  ComPDFKit PDF SDK for iOS is designed for developers to integrate viewing, editing, converting, extracting, and signing PDFs to build PDF viewer and editor on iOS.
                   DESC

  spec.homepage     = "https://www.compdf.com"
  spec.documentation_url = "https://pspdfkit.com/guides/ios/"
  spec.license      = { :type => 'Commercial', :file => 'https://www.compdf.com/pricing'} 
  spec.author       = { "ComPDFKit" => "support@compdf.com"}
  spec.platform     = :ios, "10.0"
  spec.source       = { :git => 'https://github.com/ComPDFKit/compdfkit-ios.git', :tag => "1.13.0"}

  spec.vendored_frameworks = "Lib/ComPDFKit.xcframework"

  spec.requires_arc = true
  spec.pod_target_xcconfig = {'VALID_ARCHS' => 'arm64 x86_64 armv7'}
  spec.library             = 'z', 'c++'
  spec.frameworks          = 'QuartzCore','CoreMedia', 'MediaPlayer', 'AVFoundation',
                          'CoreGraphics', 'Foundation', 'MobileCoreServices', 'SystemConfiguration',
                          'UIKit'
  spec.support = { 
    "Documentation": "https://www.compdf.com/guides/pdf-sdk/ios/overview",
    "Issues": "https://github.com/ComPDFKit/compdfkit-pdf-sdk-ios-swift/issues",
    "Source Code": "https://github.com/ComPDFKit/compdfkit-pdf-sdk-ios-swift",
    "Chat": "https://github.com/orgs/ComPDFKit/discussions"
    "Changelog": "https://www.compdf.com/pdf-sdk/changelog-ios"
  }

end
