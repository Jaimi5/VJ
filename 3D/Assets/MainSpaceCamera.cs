using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainSpaceCamera : MonoBehaviour
{
    public Vector3 target;
    public float distance;
    // Update is called once per frame
    void Update()
    {
        int DistanceAway = -3;
        int upDistance = -1;
        Vector3 PlayerPOS = GameObject.Find("SpaceShip").transform.transform.position;
        GameObject.Find("MainCamera").transform.position = new Vector3(PlayerPOS.x, PlayerPOS.y - upDistance, PlayerPOS.z - DistanceAway);
    }
}
