using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEditor;

public class WinMenu : MonoBehaviour
{
    public static WinMenu winMenu;

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Initialize() {
        Time.timeScale = 0f;
        this.gameObject.SetActive(true);
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;
    }

    public void QuitGame() {
        Application.Quit();
    }

    public void NextLevel() {
        this.gameObject.SetActive(false);
        Time.timeScale = 1f;
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void LoadMenu() {
        Time.timeScale = 1f;
        SceneManager.LoadScene(0);
    }

}
