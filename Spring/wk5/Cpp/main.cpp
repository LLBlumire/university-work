/* main.cpp
 * This exists to provide a tui interface in order to interact with a virtual library.
 * All TUI handling code is contained within this file. As well as menu processing, and data
 * interaction.
 *
 * It relies heavily on typeclasses to provide generic interfaces for it's TUI.
 */

#define CATCH_CONFIG_RUNNER
#include "book.hpp"
#include "bookbot.hpp"
#include "bookdrop.hpp"
#include "bookpile.hpp"
#include "catch.hpp"
#include "category.hpp"
#include "storagepile.hpp"
#include <iostream>
#include <map>

class GenericMenu {
    public:
        std::string Title;
        std::string Underline;
        std::string PostTitleBody;
        bool EnableUnderline;
        std::map<int, std::string> Options;
        GenericMenu(std::string title = "", std::string underline = "=", bool enableUnderline=true) {
            this->Title = title;
            this->Underline = underline;
            this->Options = std::map<int, std::string> ( );
            this->PostTitleBody = "";
            this->EnableUnderline = enableUnderline;
        }
        bool RegisterMenuOption(int opt, std::string descriptor) {
            // maybe needs `new`
            return this->Options.insert( std::pair<int, std::string> ( opt, descriptor ) ).second;
        }
        bool DeregisterMenuOption(int opt) {
            return (this->Options.erase(opt) != 0);
        }
        int Menu(std::ostream& os = std::cout, std::istream& is = std::cin) {
            os << this->Title << std::endl;
            std::stringstream underline;
            if (this->EnableUnderline) {
                for (std::string::iterator it = this->Title.begin(); it != this->Title.end(); ++it) {
                    underline << this->Underline;
                }
            }
            os << underline.str() << std::endl;
            os << this->PostTitleBody;
            for (std::map<int, std::string>::iterator it = this->Options.begin(); it != this->Options.end(); ++it) {
                os << it->first << ") " << it->second << std::endl;
            }
            os << "Enter Numeric Selection: ";
            int opt;
            is >> opt;
            os << std::endl;
            return opt;
        }
};

enum MainMenu {
    StoragePiles,
    BookPiles,
    BookDrops,
    BookBots,
    Exit,
};

enum CollectionMenu {
    CMCreate,
    CMRead,
    CMUpdate,
    CMDestroy,
    CMExit,
};
enum SPMenu {
    SPCreate,
    SPRead,
    SPRename,
    SPDelete,
    SPExit,
};
enum BPMenu {
    BPCreate,
    BPRead,
    BPRename,
    BPDelete,
    BPExit
};
enum BDMenu {
    BDCreate,
    BDRead,
    BDRename,
    BDDelete,
    BDCheckIn,
    BDCheckOut,
    BDExit,
};
enum BBMenu {
    BBCreate,
    BBRead,
    BBRename,
    BBDelete,
    BBPickUp,
    BBPlaceDown,
    BBExit
};
enum PileMenu {
    PMStoragePile,
    PMBookPile,
    PMBookDrop
};

int main(void) {
    std::map<std::string, StoragePile> storagePiles;
    std::map<std::string, BookPile> bookPiles;
    std::map<std::string, BookDrop> bookDrops;
    std::map<std::string, BookBot> bookBots;

    GenericMenu mainMenu ( "Library Management System" );
    mainMenu.RegisterMenuOption(StoragePiles, "Storage Piles");
    mainMenu.RegisterMenuOption(BookPiles, "Book Piles");
    mainMenu.RegisterMenuOption(BookDrops, "Book Drops");
    mainMenu.RegisterMenuOption(BookBots, "Book Bots");
    mainMenu.RegisterMenuOption(Exit, "Exit");

    GenericMenu storagePileMenu ( "Storage Pile Management System", "-" );
    storagePileMenu.RegisterMenuOption(SPCreate, "Create Storage Pile");
    storagePileMenu.RegisterMenuOption(SPRead, "Read Storage Pile");
    storagePileMenu.RegisterMenuOption(SPRename, "Rename Storage Pile");
    storagePileMenu.RegisterMenuOption(SPDelete, "Delete Storage Pile");
    storagePileMenu.RegisterMenuOption(SPExit, "Exit");

    GenericMenu bookPileMenu ( "Book Pile Management System", "-" );
    bookPileMenu.RegisterMenuOption(BPCreate, "Create Book Pile");
    bookPileMenu.RegisterMenuOption(BPRead, "Read Book Pile");
    bookPileMenu.RegisterMenuOption(BPRename, "Rename Book Pile");
    bookPileMenu.RegisterMenuOption(BPDelete, "Delete Book Pile");
    bookPileMenu.RegisterMenuOption(BPExit, "Exit");

    GenericMenu bookDropMenu ( "Book Drop Management System", "-" );
    bookDropMenu.RegisterMenuOption(BDCreate, "Create Book Drop");
    bookDropMenu.RegisterMenuOption(BDRead, "Read Book Drop");
    bookDropMenu.RegisterMenuOption(BDRename, "Rename Book Drop");
    bookDropMenu.RegisterMenuOption(BDDelete, "Delete Book Drop");
    bookDropMenu.RegisterMenuOption(BDCheckIn, "Check In Book Drop");
    bookDropMenu.RegisterMenuOption(BDCheckOut, "Check Out Book Drop");
    bookDropMenu.RegisterMenuOption(BDExit, "Exit");
    
    GenericMenu bookBotMenu ( "Book Bot Management System", "-" );
    bookBotMenu.RegisterMenuOption(BBCreate, "Create Book Bot");
    bookBotMenu.RegisterMenuOption(BBRead, "Read Book Bot");
    bookBotMenu.RegisterMenuOption(BBRename, "Rename Book Bot");
    bookBotMenu.RegisterMenuOption(BBDelete, "Delete Book Bot");
    bookBotMenu.RegisterMenuOption(BBPickUp, "Pick Up From Pile");
    bookBotMenu.RegisterMenuOption(BBPlaceDown, "Place Down To Pile");
    bookBotMenu.RegisterMenuOption(BBExit, "Exit");

    GenericMenu pileMenu ( "Select a Pile Type: ", "", false);
    pileMenu.RegisterMenuOption(PMStoragePile, "Storage Pile");
    pileMenu.RegisterMenuOption(PMBookPile, "Book Pile");
    pileMenu.RegisterMenuOption(PMBookDrop, "Book Drop");


    MainMenu menuOption = (MainMenu)-1;
    SPMenu spMenuOption = (SPMenu)-1;
    BPMenu bpMenuOption = (BPMenu)-1;
    BDMenu bdMenuOption = (BDMenu)-1;
    BBMenu bbMenuOption = (BBMenu)-1;

    while (menuOption != Exit) {
        menuOption = (MainMenu)mainMenu.Menu();
        switch (menuOption) {
            case StoragePiles:
                while (spMenuOption != SPExit) {
                    std::stringstream postBody;
                    for (std::map<std::string, StoragePile>::iterator it = storagePiles.begin(); it
                            != storagePiles.end(); ++it) {
                        postBody << it->first << " (" << displayCategory(it->second.category) << ")"
                            << std::endl;
                    }
                    storagePileMenu.PostTitleBody = postBody.str();
                    int category;
                    std::string name;
                    std::string changename;
                    std::map<std::string, StoragePile>::iterator seeker;
                    spMenuOption = (SPMenu)storagePileMenu.Menu();
                    switch (spMenuOption) {
                        case SPCreate:
                            std::cout << "Enter unique name for new Storage Pile: ";
                            std::cin >> name;
                            std::cout << (int)Biography << ") " << displayCategory(Biography) <<
                                std::endl;
                            std::cout << (int)History << ") " << displayCategory(History) <<
                                std::endl;
                            std::cout << (int)Reference << ") " << displayCategory(Reference) <<
                                std::endl;
                            std::cout << (int)Fiction << ") " << displayCategory(Fiction) <<
                                std::endl;
                            std::cout << "Enter a category for the Storage Pile: ";
                            std::cin >> category;
                            if (!storagePiles.insert(std::pair<std::string, StoragePile>(name,
                                            StoragePile((Category)category))).second) {
                                std::cout << "Storage Pile of name " << name << 
                                    " already exists!" << std::endl;
                            }
                            break;
                        case SPRead:
                            std::cout << "Enter name of Storage Pile: ";
                            std::cin >> name;
                            seeker = storagePiles.find(name);
                            if (seeker != storagePiles.end()) {
                                seeker->second.ListAllBooks(std::cout);
                            } else {
                                std::cout << "No Storage Pile named " << name << " found!" <<
                                    std::endl; 
                            }
                            break;
                        case SPRename:
                            std::cout << "Enter name of Storage Pile to rename: ";
                            std::cin >> name;
                            seeker = storagePiles.find(name);
                            if (seeker != storagePiles.end()) {
                                std::cout << "Enter a new name for " << name << ": ";
                                std::cin >> changename;
                                if (!storagePiles.insert(std::pair<std::string,
                                            StoragePile>(changename, seeker->second)).second) {
                                    std::cout << "Storage Pile of name " << name << 
                                        " already exists!" << std::endl;
                                } else {
                                    storagePiles.erase(name);
                                }
                            } else {
                                std::cout << "No Storage Pile named " << name << " found!" <<
                                    std::endl; 
                            }
                            break;
                        case SPDelete:
                            std::cout << "Enter name of Storage Pile to delete: ";
                            std::cin >> name;
                            if (storagePiles.erase(name) == 0) {
                                std::cout << "No Storage Piles name " << name << "found!" <<
                                    std::endl;
                            }
                            break;
                        case SPExit:
                            break;
                        default:
                            break;
                    }
                    std::cout << std::endl;
                } spMenuOption = (SPMenu)-1; // Reset to non exit value.
                break;

            case BookPiles:
                while (bpMenuOption != BPExit) {
                    std::stringstream postBody;
                    for (std::map<std::string, BookPile>::iterator it = bookPiles.begin(); it
                            != bookPiles.end(); ++it) {
                        postBody << it->first << std::endl;
                    }
                    bookPileMenu.PostTitleBody = postBody.str();
                    int category;
                    std::string name;
                    std::string changename;
                    std::map<std::string, BookPile>::iterator seeker;
                    bpMenuOption = (BPMenu)bookPileMenu.Menu();
                    switch (bpMenuOption) {
                        case BPCreate:
                            std::cout << "Enter unique name for new Book Pile: ";
                            std::cin >> name;
                            if (!bookPiles.insert(std::pair<std::string, BookPile>(name,
                                            BookPile())).second) {
                                std::cout << "Book Pile of name " << name << 
                                    " already exists!" << std::endl;
                            }
                            break;
                        case BPRead:
                            std::cout << "Enter name of Book Pile: ";
                            std::cin >> name;
                            seeker = bookPiles.find(name);
                            if (seeker != bookPiles.end()) {
                                seeker->second.ListAllBooks(std::cout);
                            } else {
                                std::cout << "No Book Pile named " << name << " found!" <<
                                    std::endl; 
                            }
                            break;
                        case BPRename:
                            std::cout << "Enter name of Book Pile to rename: ";
                            std::cin >> name;
                            seeker = bookPiles.find(name);
                            if (seeker != bookPiles.end()) {
                                std::cout << "Enter a new name for " << name << ": ";
                                std::cin >> changename;
                                if (!bookPiles.insert(std::pair<std::string,
                                            BookPile>(changename, seeker->second)).second) {
                                    std::cout << "Book Pile of name " << name << 
                                        " already exists!" << std::endl;
                                } else {
                                    bookPiles.erase(name);
                                }
                            } else {
                                std::cout << "No Book Pile named " << name << " found!" <<
                                    std::endl; 
                            }
                            break;
                        case BPDelete:
                            std::cout << "Enter name of Book Pile to delete: ";
                            std::cin >> name;
                            if (bookPiles.erase(name) == 0) {
                                std::cout << "No Book Pile named " << name << " found!" <<
                                    std::endl; 

                            }
                            break;
                        case BPExit:
                            break;
                        default:
                            break;
                    }
                    std::cout << std::endl;
                } bpMenuOption = (BPMenu)-1; // Reset to non exit value.
                break;

            case BookDrops:
                while (bdMenuOption != BDExit) {
                    std::stringstream postBody;
                    for (std::map<std::string, BookDrop>::iterator it = bookDrops.begin(); it
                            != bookDrops.end(); ++it) {
                        postBody << it->first << std::endl;
                    }
                    bookDropMenu.PostTitleBody = postBody.str();
                    int category;
                    std::string name;
                    std::string changename;
                    std::map<std::string, BookDrop>::iterator seeker;
                    bdMenuOption = (BDMenu)bookDropMenu.Menu();
                    switch (bdMenuOption) {
                        case BDCreate:
                            std::cout << "Enter unique name for new Book Drop: ";
                            std::cin >> name;
                            if (!bookDrops.insert(std::pair<std::string, BookDrop>(name,
                                            BookDrop())).second) {
                                std::cout << "Book Drop of name " << name << 
                                    " already exists!" << std::endl;
                            }
                            break;
                        case BDRead:
                            std::cout << "Enter name of Book Drop: ";
                            std::cin >> name;
                            seeker = bookDrops.find(name);
                            if (seeker != bookDrops.end()) {
                                seeker->second.ListAllBooks(std::cout);
                            } else {
                                std::cout << "No Book Drop named " << name << " found!" <<
                                    std::endl; 
                            }
                            break;
                        case BDRename:
                            std::cout << "Enter name of Book Drop to rename: ";
                            std::cin >> name;
                            seeker = bookDrops.find(name);
                            if (seeker != bookDrops.end()) {
                                std::cout << "Enter a new name for " << name << ": ";
                                std::cin >> changename;
                                if (!bookDrops.insert(std::pair<std::string,
                                            BookDrop>(changename, seeker->second)).second) {
                                    std::cout << "Book Drop of name " << name << 
                                        " already exists!" << std::endl;
                                } else {
                                    bookDrops.erase(name);
                                }
                            } else {
                                std::cout << "No Book Drop named " << name << " found!" <<
                                    std::endl; 
                            }
                            break;
                        case BDDelete:
                            std::cout << "Enter name of Book Drop to delete: ";
                            std::cin >> name;
                            if (bookDrops.erase(name) == 0) {
                                std::cout << "No Book Drop named " << name << " found!" <<
                                    std::endl; 

                            }
                            break;
                        case BDCheckIn:
                            std::cout << "Enter name of Book Drop to check in to: ";
                            std::cin >> name;
                            seeker = bookDrops.find(name);
                            if (seeker != bookDrops.end()) {
                                seeker->second.CheckIn();
                            } else {
                                std::cout << "Book Drop of name " << name << " not found!" <<
                                    std::endl;
                            }
                            break;
                        case BDCheckOut:
                            std::cout << "Enter name of BOok Drop to cehck out from: ";
                            std::cin >> name;
                            seeker = bookDrops.find(name);
                            if (seeker != bookDrops.end()) {
                                seeker->second.CheckOut();
                            } else {
                                std::cout << "Book Drop of name " << name << " not found!" <<
                                    std::endl;
                            }
                            break;
                        case BDExit:
                            break;
                        default:
                            break;
                    }
                    std::cout << std::endl;
                } bdMenuOption = (BDMenu)-1; // Reset to non exit value.
                break;

            case BookBots:
                while (bbMenuOption != BBExit) {
                    std::stringstream postBody;
                    for (std::map<std::string, BookBot>::iterator it = bookBots.begin(); it
                            != bookBots.end(); ++it) {
                        postBody << it->first << std::endl;
                    }
                    bookBotMenu.PostTitleBody = postBody.str();
                    int category;
                    std::string name;
                    std::string changename;
                    std::string bbname;
                    std::map<std::string, BookBot>::iterator seeker;
                    PileMenu pmOption = (PileMenu)-1;
                    bool selectionResult = false;
                    bbMenuOption = (BBMenu)bookBotMenu.Menu();
                    switch (bbMenuOption) {
                        case BBCreate:
                            std::cout << "Enter unique name for new Book Bot: ";
                            std::cin >> name;
                            if (!bookBots.insert(std::pair<std::string, BookBot>(name,
                                            BookBot())).second) {
                                std::cout << "Book Bot of name " << name << 
                                    " already exists!" << std::endl;
                            }
                            break;
                        case BBRead:
                            std::cout << "Enter name of Book Bot: ";
                            std::cin >> name;
                            seeker = bookBots.find(name);
                            if (seeker != bookBots.end()) {
                                seeker->second.ListContents(std::cout);
                            } else {
                                std::cout << "No Book Bot named " << name << " found!" <<
                                    std::endl; 
                            }
                            break;
                        case BBRename:
                            std::cout << "Enter name of Book Bot to rename: ";
                            std::cin >> name;
                            seeker = bookBots.find(name);
                            if (seeker != bookBots.end()) {
                                std::cout << "Enter a new name for " << name << ": ";
                                std::cin >> changename;
                                if (!bookBots.insert(std::pair<std::string,
                                            BookBot>(changename, seeker->second)).second) {
                                    std::cout << "Book Bot of name " << name << 
                                        " already exists!" << std::endl;
                                } else {
                                    bookBots.erase(name);
                                }
                            } else {
                                std::cout << "No Book Bot named " << name << " found!" <<
                                    std::endl; 
                            }
                            break;
                        case BBDelete:
                            std::cout << "Enter name of Book Bot to delete: ";
                            std::cin >> name;
                            if (bookBots.erase(name) == 0) {
                                std::cout << "No Book bot named " << name << " found!" << std::endl;
                            }
                            break;
                        case BBPickUp:
                            /* TODO: Write Pickup */
                            break;
                        case BBPlaceDown:
                            /* TODO: Write Place Down */
                            break;
                        case BBExit:
                            break;
                        default:
                            break;
                    }
                    std::cout << std::endl;
                } bbMenuOption = (BBMenu)-1; // Reset to non exit value.
                break;
            case Exit:
                break;
            default:
                break;
        }
    }
    return 0;
}
