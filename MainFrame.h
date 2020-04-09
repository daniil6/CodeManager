#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include "panel/panel.h"
#include <wx/listbook.h>

class CMainFrame : public wxFrame
{
private:
    wxListbook* m_choicebook;
    wxTextCtrl* m_txtFind;

    /**
     * @brief Шаблон функция для получения класса СPanel и выполнения её функции
     * @param numPage - номер страницы в wxListbook
     * @param func - функция выполнения
     * @param error - значение возвращаемое в случае ошибки
     * @param param - параметры передаваемы в функцию
     * @return перееменную функции
     */
    template <typename TReturn, typename TClass, typename... TParam>
    TReturn GetClassMethod(int numPage, TReturn (TClass::*func)(TParam...), TReturn error, TParam&&... param);

    /**
     * @brief Выравнивает столбцы на всех страницах wxListbook по максимальным размерам колнки
     */
    void ResizePageInListbook();

    /**
     * @brief Создание Menu
     */
    void CreateMenuBar();

    /**
     * @brief Загрузка xml - файла
     */
    void LoadXml();

    /**
     * @brief Сохранение xml - файла
     * @param event
     */
    void OnSaveXml(wxCommandEvent& event);

    /**
     * @brief Добавление нового элемента на страницу в таблицу
     * @param event
     */
    void OnAddNewItem(wxCommandEvent& event);

    /**
     * @brief Удаление элемента на странице из таблицы
     * @param event
     */
    void OnDeleteItem(wxCommandEvent& event);

    /**
     * @brief Добавление новой страницы wxListbook
     * @param event
     */
    void OnAddPage(wxCommandEvent& event);

    /**
     * @brief Удаление страницы wxListbook
     * @param event
     */
    void OnDeletePage(wxCommandEvent& event);

    /**
     * @brief Поиск в page и panel
     * @param event
     */
    void OnEditTxtFind(wxCommandEvent& event);

public:
    CMainFrame(wxWindow* parent = nullptr);
    ~CMainFrame();
};

#endif // CMAINFRAME_H