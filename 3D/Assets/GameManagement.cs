using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class GameManagement : MonoBehaviour {
    public static GameManagement Instance { get; private set; }
    public GameObject Asteroids;
    public List<Transform> asteroids;
    public int Level = 1;
    public int SendAsteroidEvery = 1; //In Seconds
    public bool PeriodicAsteroids = false;


    private float LastAsteroidSend = 3;
    private Transform Player;
    private void Awake() {
        SendAsteroidEvery = 2;
        Instance = this;
        PeriodicAsteroids = false;
    }
    // Start is called before the first frame update
    void Start() {
        //Get all Asteroids
        for (int i = 0; i < Asteroids.transform.childCount; i++)
            asteroids.Add(Asteroids.transform.GetChild(i));

        Player = FindObjectsOfType<GameObject>().First(g => g.name.Contains("SpaceShip")).transform;
    }

    // Update is called once per frame
    void Update() {
        LastAsteroidSend += Time.deltaTime;
        if (PeriodicAsteroids && LastAsteroidSend > SendAsteroidEvery) {
            int i = Random.Range(0, asteroids.Count() - 1);
            Asteroid astr = asteroids[i].GetComponent<Asteroid>();
            if (astr.isOutedOrDestroyed) {
                LastAsteroidSend = 0;
                astr.isOutedOrDestroyed = false;
                SetPositionAseroid(astr, Random.Range(1, 5));
                asteroids[i].position = astr.InitialPosition;
                astr.movementSpeed = 10.0f;
                astr.health = astr.FirstHealth;
            }

        }
    }

    private void SetPositionAseroid(Asteroid astr, int direction) {
        Vector3 asteroidPos = Player.position;
        switch (direction) {
            case 1:
                astr.Direction = new Vector3(1, 0, 0);
                astr.InitialPosition = new Vector3(asteroidPos.x - 10, asteroidPos.y, asteroidPos.z + 10);
                break;
            case 2:
                astr.Direction = new Vector3(0, 1, 0);
                astr.InitialPosition = new Vector3(asteroidPos.x, asteroidPos.y - 10, asteroidPos.z + 10);
                break;
            case 3:
                astr.Direction = new Vector3(-1, 0, 0);
                astr.InitialPosition = new Vector3(asteroidPos.x + 10, asteroidPos.y, asteroidPos.z + 10);
                break;
            case 4:
                astr.Direction = new Vector3(0, -1, 0);
                astr.InitialPosition = new Vector3(asteroidPos.x, asteroidPos.y + 10, asteroidPos.z + 10);
                break;
            default:
                astr.Direction = new Vector3(1, 1, 0);
                astr.InitialPosition = new Vector3(asteroidPos.x - 10, asteroidPos.y - 10, asteroidPos.z + 10);
                break;
        }

        
    }
}
