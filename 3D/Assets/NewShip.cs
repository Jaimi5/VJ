using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewShip : MonoBehaviour {

    public 
    public float Velocity = 0.0f;



    // Start is called before the first frame update
    void Start() {

    }

    // Update is called once per frame
    void Update() {

        if(CalculateDistance() > 50) {
            Dispara();
        }

    }

    private void Dispara(Vector3 posicion) {
        
    }

    private int CalculateDistance() {
        return Vector3.Distance(this.transform.position, EnemyShip.position);
    }

}
