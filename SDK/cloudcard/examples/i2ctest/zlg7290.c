/****************************************************************************
 * apps/examples/i2ctest/zlg7290.c
 * Driver for SPI-based MX25L6433F (64Mbit) flash.
 *
 * Copyright (C) 2015 The YunOS Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *

 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <poll.h>
#include <errno.h>
#include <nuttx/fs/fs.h>
#include <nuttx/i2c.h>
#include <nuttx/kmalloc.h>
#include "zlg7290.h"

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static ssize_t zlg7290_read(FAR struct file *filep, FAR char *buffer,
                 size_t buflen);
static ssize_t zlg7290_write(FAR struct file *filep, FAR const char *buffer,
                 size_t buflen);
static int zlg7290_open(FAR struct file *filep);
static int zlg7290_close(FAR struct file *filep);


/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct file_operations zlg7290_fops =
{
    zlg7290_open,            /* open */
    zlg7290_close,           /* close */
    zlg7290_read,            /* read */
    zlg7290_write,           /* write */
    0,                       /* seek */
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int zlg7290_open(FAR struct file *filep)
{
    return OK;
}


static int zlg7290_close(FAR struct file *filep)
{
    return OK;
}

/****************************************************************************
 * Name: zlg7290_read
 ****************************************************************************/

static ssize_t zlg7290_read(FAR struct file *filep, FAR char *buffer, size_t len)
{
    FAR struct inode        *inode = filep->f_inode;
    FAR struct zlg7290_dev_s *priv  = inode->i_private;
    uint8_t keyaddress = 0x01;

    if (!buffer)
    {
        printf("Buffer is null\n");
        return -1;
    }

    I2C_WRITE(priv->i2c, &keyaddress, 1);
    I2C_READ(priv->i2c, (uint8_t *)buffer, 1);

  return 0; /* Return EOF */
}

/****************************************************************************
 * Name: zlg7290_write
 ****************************************************************************/

static ssize_t zlg7290_write(FAR struct file *filep, FAR const char *buffer, size_t len)
{
    FAR struct inode        *inode = filep->f_inode;
    FAR struct zlg7290_dev_s *priv  = inode->i_private;
              
    uint8_t TXLength = 3;
    uint8_t keybit1 = 0;
    uint8_t data[3] = {0,0,0};
    int keynum = 0;

    if (!buffer)
    {
        printf("Buffer is null\n");
        return -1;
    }
    
    keynum = (int)*buffer;
    if(keynum < 10)
    {
        data[0] = 0x07;
        data[1] = 0x60;
        data[2] = 0x1f;
        I2C_WRITE(priv->i2c, data, TXLength);

        data[0] = 0x07;
        data[1] = 0x61;
        data[2] = keynum;
        I2C_WRITE(priv->i2c, data, TXLength);
    }
    else
    {
        keybit1 = keynum%10;
        keynum /= 10;
        data[0] = 0x07;
        data[1] = 0x61;
        data[2] = keybit1;
        I2C_WRITE(priv->i2c, data, TXLength);

        data[0] = 0x07;
        data[1] = 0x60;
        data[2] = keynum;
        I2C_WRITE(priv->i2c, data, TXLength);
    }

  return len; /* Say that everything was written */
}

/****************************************************************************
 * Name: zlg7290_register
 *
 * Description:
 *   Register /dev/zlg7290
 *
 ****************************************************************************/

struct zlg7290_dev_s * zlg7290_register(FAR struct i2c_dev_s *dev_i2c)
{
    FAR struct zlg7290_dev_s *priv = NULL;
    int ret = 0;

    /* Initialize the zlg7290 device structure */

    priv = (FAR struct zlg7290_dev_s *)kmm_malloc(sizeof(struct zlg7290_dev_s));
    if (!priv)
    {
        printf("Failed to allocate instance\n");
        return NULL;
    }

    priv->i2c = dev_i2c;
    priv->addr = 0x38;
    priv->freq = 100000;

    /* Configure I2C before using it */

    I2C_SETADDRESS(priv->i2c, priv->addr, 7);
    I2C_SETFREQUENCY(priv->i2c, priv->freq);

    ret = register_driver("/dev/zlg7290", &zlg7290_fops, 0666, priv);
    if (ret < 0)
    {
        printf("Failed to register driver: %d\n", ret);
        kmm_free(priv);
        return NULL;
    }
    return priv;  
}



/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: zlg7290_initialize
 *
 * Description:
 *   get the i2c bus then Iinitialize and register the zlg7290 device
 *
 ****************************************************************************/

struct zlg7290_dev_s * zlg7290_initialize(void)
{
    FAR struct i2c_dev_s *i2c = NULL;
    struct zlg7290_dev_s * zlg_dev = NULL;

    printf("Initializing zlg7290!\n");

    /* Initialize I2C */

    i2c = up_i2cinitialize(2);

    if (!i2c)
    {
        return NULL;
    }

    /* Then register the barometer sensor */

    zlg_dev = zlg7290_register(i2c);
    if (!zlg_dev)
    {
        printf("Error registering zlg7290\n");
    }

    return zlg_dev;

}


/****************************************************************************
 * Name: zlg7290_uninitialize
 *
 * Description:
 *   release the i2c bus then uniinitialize and unregister the zlg7290 device
 *
 ****************************************************************************/

int zlg7290_uninitialize(FAR struct zlg7290_dev_s *zlg_dev)
{
    int ret = 0;
    
    ret = unregister_driver("/dev/zlg7290");
    
    if(zlg_dev)
    {
       printf("zlg7290_uninitialize\n");
       
       ret = up_i2cuninitialize(zlg_dev->i2c);
       
       kmm_free(zlg_dev); 
    }
    return ret;
}


