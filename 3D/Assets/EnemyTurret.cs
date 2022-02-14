using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyTurret : EnemyShip {
    public GameObject topTurret;
    public bool isTurret2 = false;

    void Update() {
        pointAtShip();
        if (!Destroyed) {
            if (Time.time > nextShoot && Vector3.Distance(targetShip.transform.position, transform.position) < range) {
                nextShoot = Time.time + shootOffset;
                Shoot();
            }
        } else {
            transform.gameObject.GetComponent<Renderer>().enabled = false; //No funciona WTF?
            TimeBeenDestroyed += Time.deltaTime;
            if (TimeBeenDestroyed >= 2) {
                ExplosionMat.Instance.transform.position = ExplosionMat.Instance.InitialPosition;
                Destroy(gameObject);
            }
        }
    }

    private void Shoot() {
        RaycastHit hit;
        muzzle.Play();
        PlaySound(EnemyShotAudio);
        int frwMult = 1;
        if (isTurret2) {
            frwMult = -1;
        }
        if (Physics.Raycast(topTurret.transform.position, frwMult * topTurret.transform.forward, out hit)) {
            print("HIT");

            Ship target = hit.transform.GetComponent<Ship>();
            if (target != null) {
                target.TakeDamage(damage);
            }
            GameObject impactGO = Instantiate(impactEffect, hit.point, Quaternion.LookRotation(hit.normal));
            Destroy(impactGO, 2f);
        }
    }

    protected void pointAtShip() {
        topTurret.transform.LookAt(targetShip.transform);
        if (isTurret2) {
            topTurret.transform.Rotate(0.0f, 180.0f, 0.0f);
        }
    }
}
