#include "prompt.h"

/***@brief
 * LocationPrompt
 */
LocationPrompt::LocationPrompt(QWidget *parent, QString _label_name) : QDialog(parent)
{
    label_name = _label_name;
    add = new QPushButton("add");
    lineEdit = new QLineEdit();
    label = new QLabel("Add " + label_name + ": ");
    label->setBuddy(lineEdit);
    lay = new QHBoxLayout();
    lay->addWidget(label);
    lay->addWidget(lineEdit);
    lay->addWidget(add);
    setLayout(lay);
    setWindowTitle("Add " + label_name);
    setFixedSize(QSize(350, 100));
    // enables
    add->setEnabled(false);
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableAddButton(QString)));

    // clicking
    connect(add, SIGNAL(clicked()), this, SLOT(addClicked()));
    setStyleSheet("background-color: rgb(134, 142, 150)");
}

void LocationPrompt::enableAddButton(const QString &text)
{
    add->setEnabled(not text.isEmpty());
}

void LocationPrompt::setVideo(Video *v)
{
    vid = v;
}

void LocationPrompt::addClicked()
{
    this->hide();

    // checks if we have int input
    QString text = lineEdit->text();
    bool intFound = false;
    for (int i = 0; i < text.size(); i++) {
        if (text[i].isDigit()) {
            intFound = false;
            break;
        }
    }

    // The input is invalid - let the user know.
    if (intFound) {
        QMessageBox::information(this, "Failure", "Failed to add" + label_name);
        return;
    }
    emit(newLocation(text.toStdString(), vid));
}

LocationPrompt::~LocationPrompt()
{
    delete lay;
    delete add;
    delete label;
    delete lineEdit;
}

/**
 * @brief TagPrompt
 */

TagPrompt::TagPrompt(QWidget *parent, QString label_name) : LocationPrompt(parent, label_name) { }

/**
 * @brief RemoveTagPrompt
 */

RemoveTagPrompt::RemoveTagPrompt() : QDialog()
{
    label = new QLabel("Select the tag: ");
    remove_button = new QPushButton("remove");
    lay = new QVBoxLayout();
    options_container = new QButtonGroup();
    lay->addWidget(label);

    setLayout(lay);
    setWindowTitle("Remove tag");
    setFixedSize(QSize(150, 140));
    remove_button->setEnabled(false);
    // clicking
    connect(remove_button, &QCheckBox::clicked, this, &RemoveTagPrompt::removeClicked);
    setStyleSheet("background-color: rgb(134, 142, 150)");

}

/**
 * @brief RemoveTagPrompt::displayCurrentTags
 *
 * Adds tag options to widget
 */
void RemoveTagPrompt::displayCurrentTags()
{
    if (vid == NULL)
        return;

    for (int i = 0; i < (int)options.size(); i++) {
        lay->removeWidget(options.at(i));
        options_container->removeButton(options.at(i));
        delete options.at(i);
    }
    options.clear();
    lay->removeWidget(remove_button);

    for (int i = 0; i < (int)vid->tags.size(); i++) {
        QRadioButton *qb = new QRadioButton(QString(vid->tags[i].c_str()));

        options_container->addButton(qb);
        options.push_back(qb);
        lay->addWidget(qb);
    }
    lay->addWidget(remove_button);

    // remove button only works if choice is selected
    for (int i = 0; i < (int)options.size(); i++) {
        connect(options.at(i), &QRadioButton::toggled, this, &RemoveTagPrompt::enableRemoveButton);
    }
}

RemoveTagPrompt::~RemoveTagPrompt()
{
    delete options_container;
    delete label;
    delete remove_button;
    delete lay;
}

void RemoveTagPrompt::enableRemoveButton()
{
    remove_button->setEnabled(true);
}

/**
 * @brief RemoveTagPrompt::removeClicked
 *
 * Deletes the selected tag
 */
void RemoveTagPrompt::removeClicked()
{
    if (vid->removeTag(options_container->checkedButton()->text().toStdString())) {
        QMessageBox::information(this, tr("Success"), tr("Tag removed successfully."));
        emit(tagRemoved());
    }
    this->hide();
}

/**
 * @brief RemoveTagPrompt::setVideo
 * @param v
 *
 * Used to select the corresponding video recieved
 */
void RemoveTagPrompt::setVideo(Video *v)
{
    vid = v;
}
