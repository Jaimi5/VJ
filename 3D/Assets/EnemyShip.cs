using System.Collections;
using System.Collections.Generic;
using System.Security.Cryptography;
using UnityEngine;

public class EnemyShip : MonoBehaviour {

    // Enemy
    public float health = 50f;
    public GameObject targetShip;
    public bool isSuicideTarget = false;


    // Shooting
    public float shootOffset = 0.1f;
    public float nextShoot = 0.0f;
    public float damage = 10f;
    public float range = 100f;

    // public Camera fpsCam;
    public ParticleSystem muzzle;
    public GameObject impactEffect;

    // Movement
    public float movementSpeed = 1.0f;

    //Sound
    public AudioClip EnemyShotAudio;
    public AudioClip ShipExplosionClip;
    public AudioClip ShipHitClip;
    public AudioSource AudioPlayer;

    public bool Destroyed = false;
    public float TimeBeenDestroyed = 0.0f;
    private Vector3 velocity = Vector3.zero;

    protected void Start() {
        AudioPlayer = GetComponent<AudioSource>();
    }
    // Update is called once per frame
    void Update() {
        if (!Destroyed) {
            Vector3 targetPos = targetShip.transform.position;
            bool shouldChase = Vector3.Distance(this.transform.position, targetPos) < range;

            if (Time.time > nextShoot) {
                nextShoot = Time.time + shootOffset;
                if (shouldChase) {
                    Shoot();
                }
            }

            if (shouldChase) {
                chaseTarget(targetPos);
            }
        } else {
            transform.gameObject.GetComponent<Renderer>().enabled = false;
            TimeBeenDestroyed += Time.deltaTime;
            if (TimeBeenDestroyed >= 1) {
                ExplosionMat.Instance.transform.position = ExplosionMat.Instance.InitialPosition;
                Destroy(gameObject);
            }
        }

    }

    protected void chaseTarget(Vector3 tgtPos) {
        this.transform.position = Vector3.SmoothDamp(this.transform.position, new Vector3(tgtPos.x, tgtPos.y, isSuicideTarget ? tgtPos.z : tgtPos.z + 3), ref velocity, Time.deltaTime, isSuicideTarget ? 40.0f : 20.0f);
    }

    public void TakeDamage(float ammount) {
        PlaySound(ShipHitClip);
        print("TAKE DAMAGE");
        health -= ammount;
        if (health <= 0) {
            Die();
        }

    }

    protected void Die() {
        if (!Destroyed) {
            Destroyed = true;
            PlaySound(ShipExplosionClip);
            ExplosionMat.Instance.transform.position = transform.position;
            TimeBeenDestroyed = 0.0f;
            GameSystem.Instance.OneEnemieLess();
        }
    }

    public void PlaySound(AudioClip sound) {
        AudioPlayer.clip = sound;
        AudioPlayer.loop = false;
        AudioPlayer.Play();
    }

    protected void Shoot() {
        RaycastHit hit;
        muzzle.Play();
        //PlaySound(EnemyShotAudio);
        if (Physics.Raycast(this.transform.position, this.transform.forward, out hit)) {
            print("HIT");

            Ship target = hit.transform.GetComponent<Ship>();
            if (target != null) {
                target.TakeDamage(damage);
            }
            GameObject impactGO = Instantiate(impactEffect, hit.point, Quaternion.LookRotation(hit.normal));
            Destroy(impactGO, 2f);
        }
    }

    private void OnTriggerEnter(Collider other) {
        if (other.transform != transform && !transform.name.Contains("Turret"))
            Die();
    }
}
