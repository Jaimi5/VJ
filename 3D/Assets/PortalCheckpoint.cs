using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PortalCheckpoint : MonoBehaviour {
    public bool EntersPortal = true;
    public bool finishPortal = false;

    public WinMenu winMenu;

    void OnTriggerEnter(Collider other) {
        if (other.gameObject.transform.name == "SpaceShip") {
            GameManagement.Instance.PeriodicAsteroids = EntersPortal;
            Ship.Instance.PlaySound(Ship.Instance.PortalSoundClip);
            if (finishPortal) {
                winMenu.Initialize();
            }
        }
    }
}
