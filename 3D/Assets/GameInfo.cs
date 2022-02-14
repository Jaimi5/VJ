using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameInfo : MonoBehaviour
{
    public static GameInfo Instance { get; private set; }

    public Text TimerText;
    public Text ScoreText;
    public Text LifeText;
    public Text EnemiesLeftText;
    public Text GodModeText;
    public Text InmunityText;

    void Awake() {
        Instance = this;
    }

    public void UpdateTimer(float time) {
        TimerText.text = time.ToString("N1");
    }

    public void UpdateScore(int score) {
        ScoreText.text = score.ToString();
    }

    public void UpdateLife(float life) {
        LifeText.text = life.ToString();
    }

    public void UpdateNumberEnemies(int Enemies) {
        EnemiesLeftText.text = Enemies.ToString();
    }

    public void GodMode(bool isOn) {
        GodModeText.enabled = isOn;
    }

    public void InmunityMode(bool isOn) {
        InmunityText.enabled = isOn;
    }
}
