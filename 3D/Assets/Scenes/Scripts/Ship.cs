using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;
using UnityEngine.SocialPlatforms;
using System;
using System.Linq;
using TMPro;

public class Ship : MonoBehaviour {
    public static Ship Instance { get; private set; }
    private Transform ShipModel;

    // Menus
    public WinMenu winMenu;
    public PauseMenu pauseMenu;
    public DeathMenu deathMenu;

    public float health = 50f;

    [Header("Player Settings")]
    public Camera MainCamera;
    public float MouseSensitivity = 10.0f;

    [Space]

    [Header("Player Settings")]
    public float PlayerSpeed = 20;
    public float burstSpeed = 3;
    public bool IsRot = false;
    public bool IsRotY = false;
    public float rotSpeed = 0.1f;
    public float rotTime = 0.0f;
    public int rotSteps = 5;
    public int rotStepsCount = 0;
    bool rotDirec = false;
    bool continueRot = false;

    [Space]

    [Header("Player Debuging")]
    // Shooting
    public float damage = 10f;
    public float range = 100f;
    public bool Immortal = false;

    public float laserTime = 0.0f;
    public float laserOffset = 0.1f;

    public TextMeshProUGUI hitText;
    public TextMeshProUGUI dmgText;
    public float hitTextOffset = 1.0f;
    public float hitTextTime = 0.0f;
    public float dmgTextOffset = 0.1f;
    public float dmgTextTime = 0.0f;

    [Space]

    [Header("Audio")]
    public AudioClip ShotAudioClip;
    public AudioClip ShipExplosionClip;
    public AudioClip PortalSoundClip;
    public AudioClip ShipHitClip;
    public AudioClip MainMusicClip;
    public AudioSource MainMusicPlayer;
    private AudioSource AudioPlayer;

    [Space]

    [Header("others")]
    float m_VerticalAngle, m_HorizontalAngle;

    public Camera fpsCam;
    public ParticleSystem muzzle;
    public LineRenderer muzzleLaser;
    public GameObject impactEffect;

    private bool isAlive = true;
    int Score = 0;

    // Roll
    public bool isRolling = false;
    public float rollTime = 0.0f;
    public int rollSteps = 36;
    public int rollStepsCount = 0;
    public bool rollDirec = false;
    public float rollTick = 0.0f;
    public float rollSideStep = 10.0f;

    void Awake() {
        Instance = this;
    }

    private void Start() {
        ShipModel = transform.GetChild(0);
        AudioPlayer = GetComponent<AudioSource>();
        muzzleLaser.enabled = false;
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
        StartMusic();
        GameInfo.Instance.GodMode(Immortal);
    }

    private void Update() {
        if (!isAlive) return;
        float x = Input.GetAxis("Horizontal");
        float y = Input.GetAxis("Vertical");
        bool rotated = false;
        bool rotatedY = false;

        var time = Time.deltaTime;

        // Laser
        if (laserTime < Time.time) {
            muzzleLaser.enabled = false;
        }

        // Hit Text
        if (hitTextTime < Time.time) {
            hitText.gameObject.SetActive(false);
        }

        if (dmgTextTime < Time.time) {
            dmgText.gameObject.SetActive(false);
        }


        // Pause Menu
        if (Input.GetKeyUp(KeyCode.Escape)) {
            pauseMenu.Pause();
        }

        if (!pauseMenu.gameObject.active && !winMenu.gameObject.active && !isRolling) {
            if (Input.GetKey(KeyCode.W)) {
                print("WWWW");
                float ps = PlayerSpeed;
                if (Input.GetKey(KeyCode.LeftShift)) {
                    ps = ps * burstSpeed;
                }
                LocalMovement(x, y, ps);
            }
            if (Input.GetKey(KeyCode.D)) {
                rotated = true;
                rotDirec = true;
                SideMovement(x, y, "I");
            } else if (Input.GetKey(KeyCode.A)) {
                rotated = true;
                rotDirec = false;
                SideMovement(x, y, "D");
            }

            if (Input.GetKey(KeyCode.Space)) {
                rotatedY = true;
                UpMovement(x, y, "U");
            } else if (Input.GetKey(KeyCode.S)) {
                rotatedY = true;
                UpMovement(x, y, "D");
            }

            if (Input.GetButtonDown("Fire1")) {
                // Shooting
                Shoot();
            }

            if (Input.GetKeyDown(KeyCode.Q)) {
                isRolling = true;
                rollDirec = true;
                rollStepsCount = rollSteps;
            } else if (Input.GetKey(KeyCode.E)) {
                isRolling = true;
                rollDirec = false;
                rollStepsCount = rollSteps;
            }
            if (Input.GetKey(KeyCode.G)) {
                Immortal = !Immortal;
                GameInfo.Instance.GodMode(Immortal);
            }

            if (!rotated & IsRot) {
                rotateBack();
            }
            if (!rotatedY & IsRotY) {
                rotateBackY();
            }

            CameraRotation();
        }
        if (isRolling) {
            continueRoll();
        }
    }

    private void continueRoll() {
        if (rollTick < Time.time) {
            rollStepsCount -= 1;
            float angleToRot = 360 / rollSteps;
            if (!rollDirec) {
                angleToRot = -1 * angleToRot;
            }
            transform.Rotate(0.0f, 0.0f, angleToRot);

            //The movement of left or right of the Roll
            float spaceToMove = -(rollSideStep / rollSteps);
            if (!rollDirec) {
                spaceToMove = -1 * spaceToMove;
            }
            transform.position = new Vector3(transform.position.x + spaceToMove, transform.position.y, transform.position.z);
            rollTick = Time.time + (rollTime / rollSteps);
        }
        if (rollStepsCount <= 0) {
            isRolling = false;
            rollTime = 0.0f;
        }
    }

    private void CameraRotation() {
        // Turn player
        float turnPlayer = Input.GetAxis("Mouse X") * MouseSensitivity;
        m_HorizontalAngle = m_HorizontalAngle + turnPlayer;
        //m_HorizontalAngle = Mathf.Clamp(m_HorizontalAngle, -89.0f, 89.0f); //Limitation of 90º

        if (m_HorizontalAngle > 360) m_HorizontalAngle -= 360.0f;
        if (m_HorizontalAngle < 0) m_HorizontalAngle += 360.0f;

        Vector3 currentAngles = transform.localEulerAngles;
        currentAngles.y = m_HorizontalAngle;
        transform.localEulerAngles = currentAngles;

        // Camera look up/down
        var turnCam = -Input.GetAxis("Mouse Y");
        turnCam = turnCam * MouseSensitivity;
        m_VerticalAngle = Mathf.Clamp(turnCam + m_VerticalAngle, -89.0f, 89.0f); //Limitation of 90º
        currentAngles.x = m_VerticalAngle;
        transform.localEulerAngles = currentAngles;
    }

    private void ClampPosition() {
        List<Transform> planes = FindObjectsOfType<GameObject>().Where(g => g.name.Contains("Plane")).Select(x => x.transform).ToList();
        Transform nearestPlane = null;
        float minDist = Mathf.Infinity;
        Vector3 currentPos = transform.position;
        foreach (Transform tr in planes) {
            float dist = Vector3.Distance(tr.position, currentPos);
            if (minDist > dist) {
                nearestPlane = tr;
                minDist = dist;
            }
        }
        //This 3 pos needs to be change
        Vector3 pos = nearestPlane.position;
        pos.x = Mathf.Clamp(currentPos.x, pos.x - 6, pos.x + 6);
        pos.y = Mathf.Clamp(currentPos.y, 0, 10);
        pos.z = Mathf.Clamp(currentPos.z, 0, Mathf.Infinity);
        transform.position = pos;
    }

    private void LocalMovement(float x, float y, float playerSpeed) {
        // transform.localPosition += new Vector3(x, y, 0) * playerSpeed * Time.deltaTime;
        //Falta posar que vagi sempre amb les eix de les x, sempre a una velocitat minima per les x
        transform.position += transform.forward * Time.deltaTime * playerSpeed;
    }

    private void SideMovement(float x, float y, string direc) {
        Vector3 direction;
        Vector3 angles = transform.eulerAngles;
        if (!IsRot) {
            rotStepsCount = rotSteps;
        }

        if (direc == "I") {
            if (!IsRot) {
                if (angles.z < 280) {
                    transform.Rotate(0.0f, 0.0f, -angles.z);
                }
                float angleStep = (-30 / rotSteps);
                transform.Rotate(0.0f, 0.0f, angleStep);
                rotTime = Time.time + (rotSpeed / rotSteps);
                rotStepsCount = rotSteps - 1;
                continueRot = true;
                IsRot = true;
            } else {
                if (rotDirec && rotTime < Time.time && continueRot) {
                    float angleStep = (-30 / rotSteps);
                    transform.Rotate(0.0f, 0.0f, angleStep);
                    rotTime = Time.time + (rotSpeed / rotSteps);
                    rotStepsCount = rotStepsCount - 1;
                    if (rotStepsCount <= 0) {
                        continueRot = false;
                    }
                }
            }
            direction = transform.right;
        } else {
            if (!IsRot) {
                if (angles.z > 280) {
                    transform.Rotate(0.0f, 0.0f, -angles.z);
                }
                float angleStep = (30 / rotSteps);
                transform.Rotate(0.0f, 0.0f, angleStep);
                rotTime = Time.time + (rotSpeed / rotSteps);
                rotStepsCount = rotSteps - 1;
                continueRot = true;
                IsRot = true;
            } else {
                if (!rotDirec && rotTime < Time.time && continueRot) {
                    float angleStep = (30 / rotSteps);
                    transform.Rotate(0.0f, 0.0f, angleStep);
                    rotTime = Time.time + (rotSpeed / rotSteps);
                    rotStepsCount = rotStepsCount - 1;
                    if (rotStepsCount <= 0) {
                        continueRot = false;
                    }
                }
            }
            direction = -transform.right;
        }
        transform.position += direction * Time.deltaTime * PlayerSpeed;
    }

    private void UpMovement(float x, float y, string direc) {
        Vector3 direction;
        Vector3 angles = transform.eulerAngles;

        if (direc == "U") {
            if (!IsRotY) {
                if (angles.x < 280) {
                    transform.Rotate(-angles.x, 0.0f, 0.0f);
                }
                transform.Rotate(-40.0f, 0.0f, 0.0f);
                IsRotY = true;
            }
            direction = transform.up;
        } else {
            if (!IsRotY) {
                if (angles.x > 270) {
                    transform.Rotate(-angles.x, 0.0f, 0.0f);
                }
                transform.Rotate(40.0f, 0.0f, 0.0f);
                IsRotY = true;
            }
            direction = -transform.up;
        }
        transform.position += direction * Time.deltaTime * PlayerSpeed;
    }

    private void rotateBack() {
        Vector3 angles = transform.eulerAngles;
        float rot = -angles.z;
        if (rot < -29 && rot > -31) {
            rotStepsCount = rotSteps;
            rotTime = 0.0f;
        } else if (rot < -329 && rot > -331) {
            rotStepsCount = rotSteps;
            rotTime = 0.0f;
        }

        if (rotTime < Time.time) {
            float angleStep = (30 / rotSteps);
            if (!rotDirec) {
                angleStep = -1 * angleStep;
            }
            transform.Rotate(0.0f, 0.0f, angleStep);
            rotTime = Time.time + (rotSpeed / rotSteps);
            rotStepsCount = rotStepsCount - 1;
            if (rotStepsCount <= 0) {
                continueRot = false;
                IsRot = false;
                angles = transform.eulerAngles;
                rot = -angles.z;
                transform.Rotate(0.0f, 0.0f, rot);
            }
        }
    }

    private void rotateBackY() {
        IsRotY = false;
        Vector3 angles = transform.eulerAngles;
        float rot = -angles.x;
        transform.Rotate(rot, 0.0f, 0.0f);
    }

    public void PlaySound(AudioClip sound) {
        AudioPlayer.clip = sound;
        AudioPlayer.loop = false;
        AudioPlayer.Play();
    }

    private void Shoot() {
        RaycastHit hit;
        // Muzzle
        muzzle.Play();
        muzzleLaser.enabled = true;
        laserTime = Time.time + laserOffset;
        PlaySound(ShotAudioClip);
        if (Physics.Raycast(fpsCam.transform.position, fpsCam.transform.forward, out hit)) {
            Vector3 laserP = new Vector3(0, 0, 4);
            muzzleLaser.SetPosition(1, laserP);

            EnemyShip target = hit.transform.GetComponent<EnemyShip>();
            if (target != null) {
                Score += 100;
                target.TakeDamage(damage);
                GameInfo.Instance.UpdateScore(Score);
                hitText.gameObject.SetActive(true);
                hitTextTime = Time.time + hitTextOffset;
            }
            Asteroid asteroid = hit.transform.GetComponent<Asteroid>();
            if (asteroid != null) {
                Score += 100;
                asteroid.TakeDamage(damage);
                GameInfo.Instance.UpdateScore(Score);
                hitText.gameObject.SetActive(true);
                hitTextTime = Time.time + hitTextOffset;
            }

            Destroy(Instantiate(impactEffect, hit.point, Quaternion.LookRotation(hit.normal)), 2f);
        }
    }

    public void TakeDamage(float ammount) {

        if (!isRolling) {
            dmgText.SetText("-" + ammount.ToString());
            dmgText.gameObject.SetActive(true);
            dmgTextTime = Time.time + dmgTextOffset;
            health -= ammount;
            PlaySound(ShipHitClip);
        }
        GameInfo.Instance.UpdateLife(health);
        if (health <= 0) {
            Die();
        }


    }

    private void OnTriggerEnter(Collider other) {
        if (other?.transform?.parent?.name == "Asteroids") {
            print("Collision: Asteroid");
            Asteroid astr = other.transform.GetComponent<Asteroid>();
            TakeDamage(astr.damage);
        } else if (other.transform.name.Contains("Ciutat")) {
            print("Collision: City");
            TakeDamage(100000); //Cities
        } else if (other.transform.name.Contains("Plane")) {
            print("Collision: Plane");
            TakeDamage(100000); //Plane
        } else if (other.transform.name.Contains("Corridor")) {
            print("Collision: Plane");
            TakeDamage(100000); //Plane
        } else if (other.transform.name.Contains("Two")) {
            print("Collision: Plane");
            TakeDamage(150); //Camicaze
        } else if (other.transform != transform && !other.transform.name.Contains("Portal")) {
            print("Collision: Other");
            TakeDamage(100);
        }
    }

    private void Die() {
        ExplosionMat.Instance.transform.position = Instance.transform.position;
        PlaySound(ShipExplosionClip);
        isAlive = Immortal;
        if (!isAlive)
            deathMenu.Initialize();
    }

    private void StartMusic() {
        MainMusicPlayer.loop = true;
        MainMusicPlayer.volume = 0.4f;
        MainMusicPlayer.clip = MainMusicClip;
        MainMusicPlayer.Play();
    }



}