#ifndef SWFORM_H
#define SWFORM_H

#include <QSettings>
#include <QFutureWatcher>
#include <QTextBrowser>
#include <QTextEdit>
#include <QMainWindow>
#include <QToolButton>
#include <QCompleter>
#include <QIcon>
#include <QKeyEvent>
#include <QScrollBar>
#include <QWebView>
#include <QWebFrame>

#include "SWEnums.h"
#include "SWObject.h"

#include "ui_SWMainUI.h"

class TextEdit;
class SWObject;
class SpellListSortedModel;

class SWMainForm : public QMainWindow, public Ui::SWMainUI
{
    Q_OBJECT

    public:
        SWMainForm(QWidget* parent = 0);
        ~SWMainForm();

        void saveSettings();
        void loadSettings();

        bool isRegExp() const { return m_actionRegExp->isChecked(); }
        void setRegExp(bool enable) { m_actionRegExp->setChecked(enable); }
        SWEnums* getEnums() const { return m_enums; }
        QString getFilterText() const { return ((QTextEdit*)m_advancedTextEdit)->toPlainText(); }

        QWebView* getBrowser(quint8 num) const
        {
            switch (num)
            {
                case 1: return webView1;
                case 2: return webView2;
                case 3: return webView3;
                default: return webView1;
            }
        }

    signals:
        void signalSearch(quint8 type);

    private slots:
        void slotAbout();
        void slotAdvancedFilter();
        void slotAdvancedApply();
        void slotFilterSearch();
        void slotButtonSearch();
        void slotCompareSearch();
        void slotSearch(quint8 type);
        void slotSearchResult();
        void slotSearchFromList(const QModelIndex &index);
        void slotLinkClicked(const QUrl &url);
        void slotRegExp();
        void slotSettings();
        void slotModeShow();
        void slotModeCompare();
        void slotPrevRow();
        void slotNextRow();

        bool event(QEvent* ev);

    private:
        void loadComboBoxes();
        void detectLocale();
        void createModeButton();
        void initializeCompleter();

        SWEnums* m_enums;

        SpellListSortedModel* m_sortedModel;
        Ui::SWMainUI m_ui;
        SWObject* m_sw;
        QToolButton* m_modeButton;
        QAction* m_actionRegExp;
        QAction* m_actionAbout;
        QAction* m_actionSettings;

        TextEdit *m_advancedTextEdit;
        
        typedef QList<QEvent*> EventList;
        typedef QFutureWatcher<EventList> SearchResultWatcher;
        SearchResultWatcher* m_watcher;
};

class Enums : public QObject
{
    Q_OBJECT
public:

    enum LocalesDBC
    {
        enUS,
        koKR,
        frFR,
        deDE,
        zhCN,
        zhTW,
        esES,
        esMX
    };

    Q_ENUMS(LocalesDBC)
};

class TextEdit : public QTextEdit
{
    Q_OBJECT

    public:
        TextEdit(QWidget *parent = 0);
        ~TextEdit();

        QAbstractItemModel* setupModel();
        QCompleter *completer() const;

    protected:
        void keyPressEvent(QKeyEvent *e);
        void focusInEvent(QFocusEvent *e);

    private slots:
        void insertCompletion(const QString &completion);

    private:
        QString textUnderCursor() const;

    private:
        QCompleter *m_completer;
};

#endif