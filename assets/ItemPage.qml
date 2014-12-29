import bb.cascades 1.2

Page {
    property alias aaa: titlebar.title
    property alias type: type_label.text 
    property alias height: height_label.text
    property alias weight: weight_label.text
  
    
    
    
    titleBar: TitleBar {
        id: titlebar
    }
    Container {
        
        Container { 
            layout: StackLayout { 
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                text: "Type: "
                textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed // Show this text
            } 
            Label {
                id: type_label 
            } 
        }
        
     
        Container { 
            layout: StackLayout { 
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                text: "Height (m): "
                textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed 
            } 
            Label {
                id: height_label 
            } 
        }
        Container { 
            layout: StackLayout { 
                orientation: LayoutOrientation.LeftToRight
            }
            Label { 
                text: "Weight (kg): "
                textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.DarkRed 
            } 
            Label {
                id: weight_label 
            } 
        }
        
    }
}