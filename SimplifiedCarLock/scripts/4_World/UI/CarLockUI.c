class CarLockUI : UIScriptedMenu
{
    private EditBoxWidget m_EditBox;
    private CarScript m_Car;

    void CarLockUI(CarScript car)
    {
        m_Car = car;
    }

    override Widget Init()
    {
        // Use the layout from our simplified mod path
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("SimplifiedCarLock/assets/layouts/codelock.layout");
        m_EditBox = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("editbox"));
        return layoutRoot;
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        string name = w.GetName();
        if (name == "btnEnter")
        {
            OnEnter();
            return true;
        }
        if (name == "btnClear")
        {
            m_EditBox.SetText("");
            return true;
        }
        if (name.Contains("num_"))
        {
            string num = name;
            num.Replace("num_", "");
            m_EditBox.SetText(m_EditBox.GetText() + num);
            return true;
        }
        return false;
    }

    void OnEnter()
    {
        string codeStr = m_EditBox.GetText();
        if (codeStr.Length() < 4) return;

        int code = codeStr.ToInt();

        if (!m_Car.HasCode())
        {
            // Request to set new code
            m_Car.RPCSingleParam(-3999346, new Param1<int>(code), true);
            Close();
        }
        else
        {
            // Send code to server for validation and toggle
            m_Car.RPCSingleParam(-3999347, new Param1<int>(code), true);
            Close();
        }
    }

    override void Update(float timeslice)
    {
        if (GetGame().GetInput().LocalPress("UAUIBack", false))
            Close();
    }
}
