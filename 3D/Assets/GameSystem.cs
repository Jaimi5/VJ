using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class GameSystem : MonoBehaviour {
    public static GameSystem Instance { get; private set; }
    static int CurrentLevel = -1;

    public GameObject UIGame;
    public AudioSource BGMPlayer;
    public AudioClip EndGameSound;

    public float RunTime = 0.0f;
    public int TargetCount;
    public int DestroyedTarget;
    public int Score;

    public bool TimerRunning = false;

    void Awake() {
        Instance = this;
        Instantiate(UIGame);
    }

    // Start is called before the first frame update
    void Start() {
        GameInfo.Instance.UpdateTimer(0);
        GameInfo.Instance.UpdateScore(0);
        GameInfo.Instance.UpdateLife(Ship.Instance.health);
        UpdateEnemies();
        GameInfo.Instance.InmunityMode(false);
        TimerRunning = true;
    }

    // Update is called once per frame
    void Update() {
        if (TimerRunning) {
            RunTime += Time.deltaTime;

            GameInfo.Instance.UpdateTimer(RunTime);
        }
    }

    public void StartTimer() {
        TimerRunning = true;
    }

    public void StopTimer() {
        TimerRunning = false;
    }

    public void UpdateEnemies() {
        var enemies = FindObjectsOfType<GameObject>().First(g => g.name.Contains("AllEnemies")).transform;
        GameInfo.Instance.UpdateNumberEnemies(enemies.childCount);
    }
    public void OneEnemieLess() {
        GameInfo.Instance.UpdateNumberEnemies(int.Parse(GameInfo.Instance.EnemiesLeftText.text) - 1);
    }
}
