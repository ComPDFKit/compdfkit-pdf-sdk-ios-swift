
Pod::Spec.new do |spec|

  spec.name         = "ComPDFKit"
  spec.version      = "1.13.0"
  spec.summary      = "The folder of ComPDFKit_Tools includes the UI components to help conveniently integrate ComPDFKit PDF SDK."
  spec.description  = <<-DESC
  ComPDFKit_Tools have also built five standalone function programs, namely Viewer, Annotations, ContentEditor, Forms, and DocsEditor, using this UI component library. Additionally, we have developed a program called **PDFViewer** that integrates all the above-mentioned example features for reference
                   DESC

  spec.homepage     = "https://www.compdf.com"
  spec.license      = { :type => 'Commercial', :file => 'https://github.com/ComPDFKit/PDF-SDK-iOS/blob/main/LICENSE'} 
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

end
