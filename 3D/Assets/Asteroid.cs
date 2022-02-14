using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Asteroid : MonoBehaviour {

    // Enemy
    public float health = 50f;
    public float damage = 100f;
    public float FirstHealth;
    // public Camera fpsCam
    public ParticleSystem muzzle;
    public GameObject impactEffect;
    public int MakeInvisibleWhenPositionX = 40;

    // Movement
    public float movementSpeed = 0.0f;

    public Vector3 InitialPosition;
    public Vector3 Direction;
    public bool Rotation = true;

    public bool isOutedOrDestroyed = true;

    private void Start() {
        FirstHealth = health;
    }

    // Update is called once per frame
    void Update() {
        if (!isOutedOrDestroyed) {
            MoveAsteroid();
            RotateAsteroid();
        }

        IsOuted();
    }

    private void IsOuted() {
        if (isOutedOrDestroyed || Vector3.Distance(InitialPosition, transform.position) > 50)
            Die();
        else transform.gameObject.GetComponent<Renderer>().enabled = true;
    }

    private void MoveAsteroid() {
        transform.position += Direction * Time.deltaTime * movementSpeed;
    }

    private void RotateAsteroid() {
        if (Rotation) {
            transform.Rotate(0.5f, 0.5f, 0.0f);
        }
    }

    public void TakeDamage(float ammount) {
        health -= ammount;
        if (health <= 0) {
            Die();
        }

    }

    //Make the object invisible
    private void Die() {
        isOutedOrDestroyed = true;
        transform.gameObject.GetComponent<Renderer>().enabled = false;
    }
}
