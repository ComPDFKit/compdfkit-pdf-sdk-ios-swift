
Pod::Spec.new do |spec|

  spec.name         = "ComPDFKit"
  spec.version      = "2.5.2"
  spec.summary      = "Comprehensiven iOS PDF SDK solutions for developers."
  spec.description  = <<-DESC
  ComPDFKit PDF SDK for iOS is designed for developers to integrate viewing, editing, converting, extracting, and signing PDFs to build PDF viewer and editor on iOS.
                   DESC

  spec.homepage     = "https://www.compdf.com"
  spec.documentation_url = "https://www.compdf.com/guides/pdf-sdk/ios/overview"
  spec.license      = { :type => 'Commercial', :file => 'Lib/ComPDFKit.xcframework/LICENSE'} 
  spec.author       = { "ComPDFKit" => "support@compdf.com"}
  spec.platform     = :ios, "10.0"
  spec.source       = { :git => 'https://github.com/ComPDFKit/compdfkit-pdf-sdk-ios-swift.git', :tag => "2.5.2"}

  spec.vendored_frameworks = "Lib/ComPDFKit.xcframework"

  spec.requires_arc = true
  spec.pod_target_xcconfig = {'VALID_ARCHS' => 'arm64 x86_64 armv7'}
  spec.library             = 'z', 'c++'
  spec.frameworks          = 'QuartzCore','CoreMedia', 'MediaPlayer', 'AVFoundation',
                          'CoreGraphics', 'Foundation', 'MobileCoreServices', 'SystemConfiguration',
                          'UIKit'
end
