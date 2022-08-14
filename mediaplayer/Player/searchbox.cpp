#include "searchbox.h"

/**
 * @brief Searchbox
 */
SearchBox::SearchBox() : QWidget()
{
    box = new QHBoxLayout();
    line = new QLineEdit();
    search = new QPushButton("");
    search->setFixedWidth(20);



    search_options = new Menu("☰");
    options_bar = new QMenuBar();

    location = search_options->addAction("Search by location");
    location->setCheckable(true);
    tag = search_options->addAction("Search by tag");
    tag->setCheckable(true);

    options_bar->addMenu(search_options);
    options_bar->setFixedWidth(40);

    box->addWidget(search);
    box->addWidget(line);
    box->addLayout(box);
    box->addWidget(options_bar);
    setStyleSheet("background-color: rgb(134, 142, 150)");

    search_options->setStyleSheet("background-color: rgb(134, 142, 150)");
    setLayout(box);
    search->setEnabled(false);
    connect(line, &QLineEdit::textChanged, this, &SearchBox::textChanged);
    connect(search, &QPushButton::clicked, this, &SearchBox::textChanged);
}

SearchBox::~SearchBox()
{

    delete search;
    delete line;
}

void SearchBox::textChanged()
{
    // Turn on the search button.
    search->setEnabled(not line->text().isEmpty());
    emit(searchEntered(line->text(), location->isChecked(), tag->isChecked()));
}
