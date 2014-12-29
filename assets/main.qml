import bb.cascades 1.2
NavigationPane {
    id: nav
    Menu.definition: MenuDefinition {
        actions: [
            ActionItem {
                title: "Language"
                onTriggered: {
                    nav.push(languageSelection)
                }            
            }
        ]
    }
    Page {
        Container {
            Container {
                background: Color.create("#F80000")
                horizontalAlignment: HorizontalAlignment.Fill
                Label {
                    id: title
                    text: "Justin's Pokédex"
                    textStyle.fontSize: FontSize.Medium
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                    horizontalAlignment: HorizontalAlignment.Center
                    objectName: "title"
                }
            }
            DropDown {
                id: pokemon_types
                title: "Pokémon Type"
                onSelectedIndexChanged: {
                    pokedex.typeSelected(selectedValue)
                }
                options: Option {
                    text: "All Types"
                    value: -1
                    selected: true
                }
                objectName: "pokemon_types"
            }
            Label { // status text
                id: status
                text: ""
                objectName: "pokedex_status"
                textStyle.fontSize: FontSize.Small
                textStyle.color: Color.DarkMagenta
                horizontalAlignment: HorizontalAlignment.Center
            }
            ListView { 
                dataModel: pokemon_list 
                
                onTriggered: { 
                    if (indexPath.length == 1) { 
                        var chosenItem = dataModel.data(indexPath);	// Get the data from dataModel
                        var contentpage = itemPageDefinition.createObject(); // create the sub-page

                        contentpage.aaa = chosenItem.aaa  
                        contentpage.type = chosenItem.type
                        contentpage.height = chosenItem.height
                        contentpage.weight = chosenItem.weight
                        nav.push(contentpage); // Show the page
                    }
                }
            }

        }

    }
    attachedObjects: [
        ComponentDefinition {
            id: itemPageDefinition
            source: "ItemPage.qml"
        },
        Page {
            id: languageSelection
            titleBar: TitleBar {
                title: "Select Language"
            }
            RadioGroup {
                id: pokedex_languages
                onSelectedIndexChanged: {
                    pokedex.languageSelected(selectedValue)
                }

                objectName: "pokedex_languages"
            }

        }
    ]
    onPopTransitionEnded: {
        if (page.id == itemPageDefinition)
            page.destroy();

    }
}
